from dataclasses import dataclass
import math
import re
import random
from struct import Struct

from ball_tree_3d import BallTree3D
from rich import print
from naminglists import constellations, starnames, greeks


@dataclass
class CatalogRecord:
    """
    Represents a record in the catalog.
    """

    name: str
    ra: float  # Right Ascension, in radians
    dec: float  # Declination, in radians
    mag: float  # Visual magnitude
    spectral_type: str
    b_v: float  # B-V color index

    def __str__(self) -> str:
        return f"CatalogRecord({", ".join(f"{k}={v!r}" for k, v in self.__dict__.items())})"
    
@dataclass
class DatabaseRecord:
    """
    Represents a record in the database.
    """

    names: list[str]
    constellation: str
    ra: float  # Right Ascension, in radians
    dec: float  # Declination, in radians
    mag: float  # Visual magnitude
    spectral_type: str
    b_v: float

    def pack(self) -> bytes:
        """
        Packs the record into a binary format.
        """
        binary_format = Struct("< B 23s 23s 23s 23s 23s  20s d d f 18s f")
        return binary_format.pack(
            len(self.names) - self.names.count(""),
            *[name.encode("utf-8") for name in self.names],
            self.constellation.encode("utf-8"),
            self.ra,
            self.dec,
            self.mag,
            self.spectral_type.encode("utf-8"),
            self.b_v,
        )


def parse_name(catalog_name: str) -> tuple[list[str], str]:
    """
    Given a name string, return a list of names including the proper name (if
    any), the Bayer designation (if any), and the Flamsteed designation. Also
    returns the constellation name.

    Args:
        catalog_name (str): The name string to parse.
    Returns:
        tuple[list[str]]: A list of names including the proper name, Bayer designation,
        and Flamsteed designation as the first element of the tuple. The constellation
        name is the second element.
    """
    catalog_name = catalog_name.strip()
    match = re.match(
        r"(?P<flamsteed>\d*)(?P<bayer>([A-Z][a-z][a-z ]?)?)[\d ](?P<cons>[A-Z][a-zA-Z][a-zA-Z])",
        catalog_name,
    )
    if match:
        names: list[str] = []
        flamsteed = match.group("flamsteed")
        bayer = match.group("bayer").strip()
        cons = match.group("cons")
        constellation, gen_cons = (s.strip() for s in constellations[cons])
        if bayer:
            if bayer in starnames[cons]:
                names.append(starnames[cons][bayer])
            names.append(f"{greeks[bayer]} {gen_cons}")
            names.append(f"{greeks[bayer]} {cons}")
        if flamsteed:
            names.append(f"{flamsteed} {gen_cons}")
            names.append(f"{flamsteed} {cons}")
        return (names + [""] * (5 - len(names)), constellation)

    print(f"Failed to parse name: {catalog_name}")
    return ([], "")


if __name__ == "__main__":
    RADIANS_IN_HOUR: float = math.pi / 12
    RADIANS_IN_DEGREE: float = math.pi / 180
    catalog: list[CatalogRecord] = []
    coords: list[tuple[float, float, float]] = []

    with open("catalog", "r") as catalog_file:
        for line in catalog_file:
            try:
                name = line[4:14].strip()
                if not name:
                    continue  # Skip if name is empty
                name = re.sub(r"\s+", " ", name)  # Normalize whitespace

                ra_h = int(line[75:77])
                ra_m = int(line[77:79])
                ra_s = float(line[79:83])
                ra = (ra_h + (ra_m + ra_s / 60) / 60) * RADIANS_IN_HOUR

                dec_sign = int(line[83] + "1")
                dec_d = int(line[84:86])
                dec_m = int(line[86:88])
                dec_s = int(line[88:90])
                dec = dec_sign * (dec_d + (dec_m + dec_s / 60) / 60) * RADIANS_IN_DEGREE

                mag = float(line[102:107])
                spectral_type = line[127:147].strip()
                b_v = float(line[109:114])
            except ValueError:
                continue

            record = CatalogRecord(name, ra, dec, mag, spectral_type, b_v)
            catalog.append(record)
            coords.append(
                (
                    math.cos(ra) * math.cos(dec),
                    math.sin(ra) * math.cos(dec),
                    math.sin(dec),
                )
            )

    parsed_names = [parse_name(record.name) for record in catalog]
    # for i in range(5):
    #     print(f"{i}: {max(len(names[i].encode()) for names, _ in parsed_names)}")
    # print(f"Constellation: {max(len(cons.encode()) for _, cons in parsed_names)}")
    # print(f"Spectral Type: {max(len(record.spectral_type.encode()) for record in catalog)}")

    db_records = [
        DatabaseRecord(
            names=names,
            constellation=constellation,
            ra=record.ra,
            dec=record.dec,
            mag=record.mag,
            spectral_type=record.spectral_type,
            b_v=record.b_v,
        )
        for (names, constellation), record in zip(parsed_names, catalog)
    ]
    with open("db_files/db.bin", "wb") as db_file:
        for db_record in db_records:
            db_file.write(db_record.pack())

    tree = BallTree3D(coords)
    with open("db_files/ball_tree.bin", "wb") as ball_tree_file:
        for node in tree.nodes:
            ball_tree_file.write(node.pack())
