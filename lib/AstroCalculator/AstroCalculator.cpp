/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#include "AstroCalculator.h"

#include <pico.h>

#include "Arduino.h"
#include "Datatypes.h"
#include "Vectors.h"

AstroCalculator& AstroCalculator::GetInstance() {
  static AstroCalculator instance;
  return instance;
}

void AstroCalculator::SetObserverLocation(double latitude, double longitude) {
  sin_latitude_ = sin(latitude);
  cos_latitude_ = cos(latitude);
  longitude_ = longitude;
  sin_longitude_ = sin(longitude);
  cos_longitude_ = cos(longitude);
}

EquatorialCoordinates AstroCalculator::HorizontalToEquatorial(double azimuth,
                                                              double altitude) {
  double cos_altitude = cos(altitude);
  double sin_altitude = sin(altitude);
  double cos_azimuth = cos(azimuth);
  double sin_dec =
      sin_latitude_ * sin_altitude + cos_latitude_ * cos_altitude * cos_azimuth;
  double cos_ha = (sin_altitude - sin_latitude_ * sin_dec) /
                  (cos_latitude_ * sqrt(1 - sin_dec * sin_dec));
  double dec = asin(sin_dec);
  double ha = acos(cos_ha);
  if (azimuth < PI) ha = TWO_PI - ha;
  double ra = lst_ - ha;
  if (ra < 0) ra += TWO_PI;
  return {ra, dec};
}

HorizontalCoordinates AstroCalculator::EquatorialToHorizontal(double ra,
                                                              double dec) {
  double ha = lst_ - ra;
  double sin_dec = sin(dec);
  double cos_dec = cos(dec);
  double sin_altitude =
      sin_latitude_ * sin_dec + cos_latitude_ * cos_dec * cos(ha);
  double cos_azimuth = (sin_dec - sin_latitude_ * sin_altitude) /
                       (cos_latitude_ * sqrt(1 - sin_altitude * sin_altitude));
  double altitude = asin(sin_altitude);
  double azimuth = acos(cos_azimuth);
  if (ha < PI) azimuth = TWO_PI - azimuth;
  return {azimuth, altitude};
}

void AstroCalculator::SetJulianDate(double jd) {
  UpdateLst(jd);
  double t = (jd - 2451545.0) / 36525.0;
  decimal_year_ = 2000.0 + t;
}

void AstroCalculator::UpdateLst(double jd) {
  double t = (jd - 2451545.0) / 36525.0;
  double gmst = 4.8949612127358 + 6.30038809898494 * (jd - 2451545.0) +
                6.770708127e-6 * t * t - t * t * t / 2217919625.0;
  lst_ = fmod(gmst + longitude_, TWO_PI);
}

/*
MIT License

Copyright (c) 2019 Nathan Zimmerberg
Modified by Boonyakron Thanpanit, 2025

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

static constexpr int NMAX = 12;  // order of the Model
static constexpr int NUMCOF =
    (NMAX + 1) * (NMAX + 2) / 2;  // number of coefficents
// mean radius of  ellipsoid in meters from section 1.2 of the WMM2015 Technical
// report
static constexpr double EARTH_R = 6371200.0f;
struct ConstModel {
  double epoch;  // decimal year
  double Main_Field_Coeff_C[NUMCOF];
  double Main_Field_Coeff_S[NUMCOF];
  double Secular_Var_Coeff_C[NUMCOF];
  double Secular_Var_Coeff_S[NUMCOF];
  /** Function for indexing the C spherical component n,m at decimal_year_
   * time.*/
  inline double C(int n, int m, double decimal_year_) const {
    int index = (m * (2 * NMAX - m + 1)) / 2 + n;
    return Main_Field_Coeff_C[index] +
           (decimal_year_ - epoch) * Secular_Var_Coeff_C[index];
  }
  /** Function for indexing the S spherical component n,m at decimal_year_
   * time.*/
  inline double S(int n, int m, double decimal_year_) const {
    int index = (m * (2 * NMAX - m + 1)) / 2 + n;
    return Main_Field_Coeff_S[index] +
           (decimal_year_ - epoch) * Secular_Var_Coeff_S[index];
  }
};

ConstModel __in_flash() WMM = {
  2025.000000,
  {0.0,
   -29351.8,
   -2556.6,
   1361.0,
   895.0,
   -233.2,
   64.4,
   79.5,
   23.2,
   4.6,
   -1.3,
   2.9,
   -2.0,
   -1410.8,
   1703.8183794055044,
   -981.469715104173,
   252.82409893046193,
   95.24957042772772,
   13.922301397056312,
   -14.551632210855248,
   1.8,
   1.1627553482998907,
   -0.8629758239529499,
   -0.1846372364689991,
   -0.022645540682891915,
   476.11189948722483,
   160.57388953375948,
   4.15163287822461,
   9.13442468279827,
   2.6533020756713523,
   -0.2263115799444015,
   -0.34860834438919813,
   0.04767312946227961,
   0.00259499648053841,
   -0.026989594817970655,
   0.0027372445072567945,
   23.90681911087295,
   -5.599646034731634,
   -1.3814850676223365,
   -0.6653382101325865,
   0.2156720148499058,
   0.0049040823861374976,
   -0.0003467709910735329,
   0.002544603402301914,
   0.0023082472415244704,
   0.0008939803125353484,
   0.08521972068512543,
   -0.3333664004762482,
   -0.04294096373910387,
   0.008663030650303626,
   -0.00686929030326151,
   -0.0004908010366251525,
   -0.00012852188008557455,
   -5.267829510341783e-05,
   -8.070655599277452e-05,
   0.015515999877693526,
   0.0033352117122161574,
   0.00022845544963880868,
   0.0007418859893731344,
   -0.0003073885868038485,
   -8.128437404749033e-06,
   -8.296051686578281e-07,
   3.1940908071889606e-06,
   -0.003922249414665777,
   -0.0001989288712648212,
   0.00010160546755936292,
   7.270295435148324e-06,
   -1.3631803940903108e-06,
   -4.928589116323788e-07,
   2.845522253034599e-07,
   6.801413297728968e-05,
   -2.0776599777965716e-05,
   3.760266711303181e-06,
   2.755165074316402e-07,
   -8.658648477055405e-09,
   2.2208964739434834e-08,
   2.7825803274061227e-07,
   -6.523790302905397e-07,
   2.2495828630708266e-08,
   1.0925366070799884e-08,
   -4.441792947886967e-10,
   -2.2799965928230828e-07,
   -1.0947915869962772e-08,
   -1.2822351770735609e-09,
   -1.9385573719060062e-10,
   -3.536041036260129e-09,
   -3.957063665233731e-11,
   -1.193099586284436e-11,
   1.0967434505203656e-10,
   -1.143434089780942e-11,
   -1.2567827257223882e-12},
  {0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   4545.4,
   -1809.184803532611,
   -23.106853240254647,
   88.10105561229106,
   11.722229594521114,
   -4.015209180342259,
   -9.241231365075604,
   1.1833333333333331,
   -3.6969657227996526,
   0.44497190922573976,
   0.0,
   -0.14719601443879746,
   -235.29910220823197,
   30.66111815747538,
   -9.980316739574063,
   10.744659803163351,
   0.5796550698475775,
   -0.3703280399090206,
   -0.25099800796022265,
   0.19387072647993708,
   0.0,
   0.03130792998884596,
   0.006386903850265854,
   -28.961192904375405,
   4.2231410863148575,
   -1.2241133007266416,
   0.28062666079922405,
   -0.00363696483726654,
   0.027953269600983738,
   0.014390996129551616,
   0.0030535240827622968,
   -0.0005770618103811176,
   0.000744983593779457,
   -2.645332817300257,
   0.10094898042590615,
   -0.06278409857208829,
   0.012830058051715495,
   -0.003070604421273578,
   -0.0006478573683452012,
   0.0006811659644535451,
   1.755943170113928e-05,
   -8.691475260760332e-05,
   0.07876782713030063,
   0.0024398528632990682,
   -0.0006762281309308737,
   0.000557511956511172,
   -0.00012201684361679482,
   -0.00012328130063869367,
   4.14802584328914e-06,
   -0.0,
   0.0046976529233311685,
   -0.00044983015033756875,
   4.741588486103603e-06,
   2.1810886305444973e-05,
   6.05857952929027e-07,
   -2.464294558161894e-07,
   2.845522253034599e-07,
   -1.1016373651251144e-05,
   -6.430852312227483e-06,
   -2.6234418916068703e-07,
   -7.714462208085927e-07,
   -1.0390378172466486e-07,
   -4.441792947886967e-09,
   1.205784808542653e-06,
   5.998887634855538e-08,
   -9.498238755187934e-08,
   -1.6884656654872546e-08,
   3.5534343583095735e-09,
   1.7674392192426998e-07,
   3.6493052899875906e-09,
   -3.7184820135133262e-09,
   4.8463934297650154e-11,
   -8.250762417940301e-09,
   -3.561357298710358e-10,
   -5.965497931422179e-11,
   -9.701961293064772e-11,
   8.795646844468785e-13,
   3.5908077877782525e-13},
  {0.0,
   12.0,
   -11.6,
   -1.3,
   -1.6,
   0.6,
   -0.2,
   -0.0,
   -0.1,
   -0.0,
   0.1,
   0.0,
   0.0,
   9.7,
   -3.002221399786054,
   -1.7146428199482247,
   -0.758946638440411,
   0.3614784456460255,
   -0.08728715609439695,
   -0.01889822365046136,
   0.03333333333333333,
   -0.0149071198499986,
   0.0,
   -0.0,
   0.0,
   -2.309401076758503,
   0.051639777949432225,
   -0.447213595499958,
   0.0,
   0.031052950170405942,
   -0.0025717224993681985,
   0.0,
   0.0015891043154093204,
   0.001297498240269205,
   0.0,
   -0.0,
   -0.8221921916437785,
   0.11155467020454339,
   0.005976143046671968,
   0.006900655593423542,
   0.00181848241863327,
   0.0012260205965343744,
   0.0005201564866102993,
   0.0001272301701150957,
   0.0,
   -0.0,
   -0.04930066485916347,
   0.005164831556674268,
   -0.000944911182523068,
   -5.482930791331409e-05,
   -3.1655715683232764e-05,
   -5.8896124395018286e-05,
   -0.0,
   0.0,
   -0.0,
   0.000668153104781061,
   6.715191366878169e-05,
   -7.310574388441878e-05,
   1.3169573775854458e-05,
   0.0,
   -4.064218702374517e-06,
   -8.296051686578281e-07,
   -0.0,
   5.815526314990443e-05,
   -1.4337215947014143e-05,
   1.3547395674581724e-06,
   9.087869293935405e-07,
   0.0,
   0.0,
   4.7425370883909984e-08,
   3.8317821395656156e-06,
   -0.0,
   -4.372403152678118e-08,
   -1.836776716210935e-08,
   -0.0,
   -0.0,
   6.183511838680272e-08,
   7.498609543569422e-09,
   -2.499536514523141e-09,
   -9.93215097345444e-10,
   0.0,
   -1.7674392192427e-09,
   -0.0,
   -1.282235177073561e-10,
   0.0,
   -0.0,
   -1.9785318326168656e-11,
   -5.96549793142218e-12,
   -4.218244040462945e-12,
   -0.0,
   -1.7954038938891263e-13},
  {0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   -21.5,
   -15.992602456552632,
   1.632993161855452,
   -0.3478505426185218,
   -0.12909944487358055,
   0.06546536707079771,
   0.11338934190276816,
   -0.03333333333333333,
   -0.044721359549995794,
   0.0,
   -0.0,
   -0.0,
   -3.4929691285972355,
   -0.03872983346207416,
   0.30559595692497127,
   0.10734900802433867,
   -0.05520524474738834,
   0.012858612496840992,
   0.009960238411119947,
   0.004767312946227961,
   -0.0,
   0.0010795837927188264,
   0.0,
   -0.21608897344483924,
   0.03187276291558383,
   0.003984095364447979,
   -0.0023002185311411807,
   -0.002909571869813232,
   -0.0009808164772274995,
   -0.0005201564866102993,
   -0.0002544603402301914,
   -0.0,
   -7.44983593779457e-05,
   -0.03098898934004561,
   0.003991006202884661,
   0.000944911182523068,
   0.0,
   0.00012662286273293106,
   5.8896124395018286e-05,
   1.2852188008557456e-05,
   8.77971585056964e-06,
   6.208196614828809e-06,
   0.0014105454434266843,
   0.0001566877985604906,
   -9.138217985552347e-05,
   -2.1949289626424097e-05,
   4.692955523722878e-06,
   -1.3547395674581724e-06,
   -0.0,
   -0.0,
   5.815526314990443e-05,
   1.0752911960260607e-05,
   -4.064218702374517e-06,
   -3.029289764645135e-07,
   1.5146448823225676e-07,
   -0.0,
   -0.0,
   -9.579455348914039e-07,
   3.7101071032081634e-07,
   -8.744806305356236e-08,
   0.0,
   8.658648477055405e-09,
   -0.0,
   6.183511838680272e-08,
   2.999443817427769e-08,
   -2.499536514523141e-09,
   -0.0,
   0.0,
   1.7674392192427e-09,
   8.109567311083534e-10,
   0.0,
   -0.0,
   -0.0,
   0.0,
   -0.0,
   0.0,
   0.0,
   -1.7954038938891263e-13}
};

Vector3 AstroCalculator::EarthFrameNormalizedMagneticField() const {
  constexpr double a_earth = 6378137;
  constexpr double e2 = 0.0066943799901413165;  // f*(2-f);
  constexpr double e2m = 0.9933056200098587;    // (1-f)*(1-f);

  double n_earth = a_earth / sqrtf(1.0f - e2 * (sin_latitude_ * sin_latitude_));
  double z = (e2m * n_earth) * sin_latitude_;
  double r = n_earth * cos_latitude_;
  double x = r * cos_longitude_;
  double y = r * sin_longitude_;
  double px = 0;
  double py = 0;
  double pz = 0;
  double rsqrd = x * x + y * y + z * z;
  double temp = EARTH_R / rsqrd;
  double a = x * temp;
  double b = y * temp;
  double f = z * temp;
  double g = EARTH_R * temp;

  int n, m;
  // first m==0 row, just solve for the Vs
  double Vtop = EARTH_R / sqrtf(rsqrd);  // V0,0
  double Wtop = 0;                       // W0,0
  double Vprev = 0;
  double Wprev = 0;
  double Vnm = Vtop;
  double Wnm = Wtop;

  // iterate through all ms
  for (m = 0; m <= NMAX + 1; m++) {
    // iterate through all ns
    for (n = m; n <= NMAX + 1; n++) {
      if (n == m) {
        if (m != 0) {
          temp = Vtop;
          Vtop = (2 * m - 1) * (a * Vtop - b * Wtop);
          Wtop = (2 * m - 1) * (a * Wtop + b * temp);
          Vprev = 0;
          Wprev = 0;
          Vnm = Vtop;
          Wnm = Wtop;
        }
      } else {
        temp = Vnm;
        double invs_temp = 1.0f / (n - m);
        Vnm = ((2 * n - 1) * f * Vnm - (n + m - 1) * g * Vprev) * invs_temp;
        Vprev = temp;
        temp = Wnm;
        Wnm = ((2 * n - 1) * f * Wnm - (n + m - 1) * g * Wprev) * invs_temp;
        Wprev = temp;
      }
      if (m < NMAX && n >= m + 2) {
        px += 0.5f * (n - m) * (n - m - 1) *
              (WMM.C(n - 1, m + 1, decimal_year_) * Vnm +
               WMM.S(n - 1, m + 1, decimal_year_) * Wnm);
        py += 0.5f * (n - m) * (n - m - 1) *
              (-WMM.C(n - 1, m + 1, decimal_year_) * Wnm +
               WMM.S(n - 1, m + 1, decimal_year_) * Vnm);
      }
      if (n >= 2 && m >= 2) {
        px += 0.5f * (-WMM.C(n - 1, m - 1, decimal_year_) * Vnm -
                      WMM.S(n - 1, m - 1, decimal_year_) * Wnm);
        py += 0.5f * (-WMM.C(n - 1, m - 1, decimal_year_) * Wnm +
                      WMM.S(n - 1, m - 1, decimal_year_) * Vnm);
      }
      if (m == 1 && n >= 2) {
        px += -WMM.C(n - 1, 0, decimal_year_) * Vnm;
        py += -WMM.C(n - 1, 0, decimal_year_) * Wnm;
      }
      if (n >= 2 && n > m) {
        pz += (n - m) * (-WMM.C(n - 1, m, decimal_year_) * Vnm -
                         WMM.S(n - 1, m, decimal_year_) * Wnm);
      }
    }
  }
  return Vector3(cos_longitude_ * py - sin_longitude_ * px,
                 cos_latitude_ * pz - sin_latitude_ * (cos_longitude_ * px +
                                                       sin_longitude_ * py),
                 0.0)
      .Normalized();  // Return normalized vector
}
