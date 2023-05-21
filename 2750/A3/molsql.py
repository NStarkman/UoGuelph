# import the necessary modules
import sqlite3
import MolDisplay

# define a class to represent a molecule database
class Database:

    # initialise the database connection
    def __init__(self, reset=False):
        # if reset is True, delete all existing tables before creating a new one
        if reset:
            try:
                conn = sqlite3.connect("molecules.db")
        
                conn.close()
            except sqlite3.Error as e:
                # if there is an error with the database, print it to the console
                print(e)
        # attempt to create a new database connection
        try:
            self.conn = sqlite3.connect("molecules.db")
        except sqlite3.Error as e:
            # if there is an error with the database, print it to the console
            print(e)

    # create the tables for the database if they don't already exist
    def create_tables(self):
        cursor = self.conn.cursor()
        
        # create the Elements table, which stores information about chemical elements
        cursor.execute(
            """CREATE TABLE IF NOT EXISTS Elements (
            ELEMENT_NO INTEGER NOT NULL,
            ELEMENT_CODE VARCHAR(3) NOT NULL,
            ELEMENT_NAME VARCHAR(32) NOT NULL,
            COLOUR1 CHAR(6) NOT NULL,
            COLOUR2 CHAR(6) NOT NULL,
            COLOUR3 CHAR(6) NOT NULL,
            RADIUS DECIMAL(3) NOT NULL,
            PRIMARY KEY (ELEMENT_CODE)
            );
            """
        )
        
        # create the Atoms table, which stores information about each atom in a molecule
        cursor.execute(
            """CREATE TABLE IF NOT EXISTS Atoms (
            ATOM_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
            ELEMENT_CODE VARCHAR(3) NOT NULL,
            X DECIMAL(7,4) NOT NULL,
            Y DECIMAL(7,4) NOT NULL,
            Z DECIMAL(7,4) NOT NULL,
            FOREIGN KEY (ELEMENT_CODE) REFERENCES Elements(ELEMENT_CODE)
            );
            """
        )
        
        # create the Bonds table, which stores information about bonds between atoms in a molecule
        cursor.execute(
            """ CREATE TABLE IF NOT EXISTS Bonds (
            BOND_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
            A1 INTEGER NOT NULL,
            A2 INTEGER NOT NULL,
            EPAIRS INTEGER NOT NULL
            );
            """
        )
        
        # create the Molecules table, which stores information about each molecule
        cursor.execute(
            """CREATE TABLE IF NOT EXISTS Molecules (
            MOLECULE_ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
            NAME TEXT UNIQUE NOT NULL
            );"""
        )
        
        # create the MoleculeAtom table, which links atoms to the molecules they are part of
        cursor.execute(
            """ 
            CREATE TABLE IF NOT EXISTS MoleculeAtom (
            MOLECULE_ID INTEGER NOT NULL,
            ATOM_ID INTEGER NOT NULL,
            PRIMARY KEY (MOLECULE_ID, ATOM_ID),
            FOREIGN KEY (MOLECULE_ID) REFERENCES Molecules (MOLECULE_ID),
            FOREIGN KEY (ATOM_ID) REFERENCES Atoms (ATOM_ID)
            );
            """
        )
        
        # create the MoleculeBond table, which links bonds to the molecules they are part of
        cursor.execute(
            """ 
            CREATE TABLE IF NOT EXISTS MoleculeBond (
            MOLECULE_ID INTEGER NOT NULL,
            BOND_ID INTEGER NOT NULL,
            PRIMARY KEY (MOLECULE_ID, BOND_ID),
            FOREIGN KEY (MOLECULE_ID) REFERENCES Molecules(MOLECULE_ID),
            FOREIGN KEY (BOND_ID) REFERENCES Bonds(BOND_ID)
            );
            """
        )
        self.conn.commit()
        
    # define a method to insert data from a tuple into a table
    def __setitem__(self, table, values):
        cursor = self.conn.cursor()
        placeholders = ",".join(["?" for i in range(len(values))])
        query = f"INSERT OR REPLACE INTO {table} VALUES ({placeholders})"
        cursor.execute(query, values)
        self.conn.commit()

    # define a method to add an atom to the database
    def add_atom(self, molname, atom):
        element_code = atom.element
        x = atom.x
        y = atom.y
        z = atom.z
        cursor = self.conn.cursor()

       # Check if the element code is already in the Elements table.
        cursor.execute(
            "SELECT ELEMENT_CODE FROM Elements WHERE ELEMENT_CODE = ?", (element_code,)
        )

        # Insert the atom record into the Atoms table.
        cursor.execute(
            "INSERT INTO Atoms (ELEMENT_CODE, X, Y, Z) VALUES (?, ?, ?, ?)",
            (element_code, x, y, z),
        )
        atom_id = cursor.lastrowid
        self.conn.commit()

        # Get the molecule ID for the molecule name.
        cursor.execute("SELECT MOLECULE_ID FROM Molecules WHERE NAME = ?", (molname,))
        molecule_id = cursor.fetchone()[0]

        # Insert a record into the MoleculeAtom table linking the atom to the molecule.
        cursor.execute(
            "INSERT INTO MoleculeAtom (MOLECULE_ID, ATOM_ID) VALUES (?, ?)",
            (molecule_id, atom_id),
        )
        self.conn.commit()

    # define a method to add a bond to the database
    def add_bond(self, molname, bond):
        cursor = self.conn.cursor()
        a1 = bond.a1
        a2 = bond.a2
        epairs = bond.epairs
        # Insert the bond record into the Bonds table.
        cursor.execute(
            "INSERT INTO Bonds (A1, A2, EPAIRS) VALUES (?, ?, ?)", (a1, a2, epairs)
        )
        bond_id = cursor.lastrowid
        self.conn.commit()
        # Get the molecule ID for the molecule name.
        cursor.execute("SELECT MOLECULE_ID FROM Molecules WHERE NAME = ?", (molname,))
        molecule_id = cursor.fetchone()[0]
        # Insert a record into the MoleculeBond table linking the bond to the molecule.
        cursor.execute(
            "INSERT INTO MoleculeBond (MOLECULE_ID, BOND_ID) VALUES (?, ?)",
            (molecule_id, bond_id),
        )
        self.conn.commit()

    # define a method to add the whole molecule to the database
    def add_molecule(self, name, fp):
        mol = MolDisplay.Molecule()

        mol.parse(fp)

        cursor = self.conn.cursor()
        # Insert the molecule record into the Molecules table.
        cursor.execute("INSERT INTO Molecules (NAME) VALUES (?)", (name,))
        self.conn.commit()

        for i in range(mol.atom_no):
            self.add_atom(name, mol.get_atom(i))
        for i in range(mol.bond_no):
            self.add_bond(name, mol.get_bond(i))


    # define a method to load a molecule from the database
    def load_mol(self, name):
        mol = MolDisplay.Molecule()
        # Get the atoms for the molecule.
        cursor = self.conn.cursor()
        cursor.execute(
            """
                        SELECT a.ATOM_ID, a.ELEMENT_CODE, a.X, a.Y, a.Z 
                        FROM Atoms a 
                        JOIN MoleculeAtom ma 
                        ON a.ATOM_ID = ma.ATOM_ID
                        JOIN Molecules m 
                        ON ma.MOLECULE_ID = m.MOLECULE_ID
                        WHERE m.NAME = ?
                        """,
            (name,),
        )

        atoms = cursor.fetchall()
        # Add the atoms to the molecule.
        for atom in atoms:
            mol.append_atom(atom[1], atom[2], atom[3], atom[4])
        # Get the bonds for the molecule.
        cursor.execute(
            """
                        SELECT b.BOND_ID, b.A1, b.A2, b.EPAIRS
                        FROM Bonds b
                        JOIN MoleculeBond mb
                        ON b.BOND_ID = mb.BOND_ID
                        JOIN Molecules m
                        ON mb.MOLECULE_ID = m.MOLECULE_ID
                        WHERE m.NAME = ?
                        """,
            (name,),
        )

        bonds = cursor.fetchall()
        # Add the bonds to the molecule.
        for bond in bonds:
            mol.append_bond(bond[1], bond[2], bond[3])

        return mol
    
    # define a method to get the list of element colours and radii from the database
    def radius(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT ELEMENT_CODE, RADIUS FROM Elements")
        elements = cursor.fetchall()
        radius_dict = {}
        for element in elements:
            radius_dict[element[0]] = element[1]
        return radius_dict

    # define a method to get the list of elements and radii from the database
    def element_name(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT ELEMENT_CODE, ELEMENT_NAME FROM Elements")
        elements = cursor.fetchall()
        name_dict = {}
        for element in elements:
            name_dict[element[0]] = element[1]
        return name_dict

    # define a method to get the list of element colours from the database
    def radial_gradients(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT ELEMENT_NAME, COLOUR1, COLOUR2, COLOUR3 FROM Elements")
        elements = cursor.fetchall()
        gradients = ""
        # create a radial gradient for each element
        for element in elements:
            gradients += """
            <radialGradient id="%s" cx="-50%%" cy="-50%%" r="220%%" fx="20%%" fy="20%%">
            <stop offset="0%%" stop-color="#%s"/>
            <stop offset="50%%" stop-color="#%s"/>
            <stop offset="100%%" stop-color="#%s"/>
            </radialGradient>""" % (
                element[0],
                element[1],
                element[2],
                element[3],
            )
        return gradients
