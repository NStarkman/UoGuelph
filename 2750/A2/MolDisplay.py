#!/usr/bin/python
# -*- coding: utf-8 -*-
import molecule
import math
mol = molecule.molecule()
radius = {
    'H': 25,
    'C': 40,
    'O': 40,
    'N': 40,
    }
element_name = {
    'H': 'grey',
    'C': 'black',
    'O': 'red',
    'N': 'blue',
    }
header = \
    """<svg version="1.1" width="1000" height="1000"
 xmlns="http://www.w3.org/2000/svg">"""
footer = """</svg>"""
offsetx = 500
offsety = 500

#Create a Atom class that is a subclass of the atom class.
class Atom:
    def __init__(self, atom):
        self.atom = atom
        self.z = atom.z

    #Create a __str__ method that returns a string with the atom's element, x, y, and z coordinates.
    def __str__(self):
        return f"Element: {self.atom.element}, X: {self.atom.x}, Y: {self.atom.y}, Z: {self.atom.z}"

    #Create a svg method that returns a string with the atom's element, x, y, and z coordinates.
    def svg(self):
        
        x = self.atom.x * 100 + offsetx
        y = self.atom.y * 100 + offsety
        r = radius[self.atom.element]
        color = element_name[self.atom.element]
        return f'  <circle cx="{x:.2f}" cy="{y:.2f}" r="{r}" fill="{color}"/>\n'

#Create a Bond class that is a subclass of the bond class.
class Bond:
    def __init__(self, c_bond):
        self.c_bond = c_bond
        self.z = c_bond.z

    #Create a __str__ method that returns a string with the bond's atom1, atom2, and bond_type.
    def __str__(self):
        return f"Bond({self.c_bond.a1}, {self.c_bond.a2}, {self.c_bond.bond_type}, z={self.z})"

    #Create a svg method that returns a string with the bond's atom1, atom2, and bond_type.
    def svg(self):
        x1 = self.c_bond.x1 * 100 + offsetx
        x2 = self.c_bond.x2 * 100 + offsetx
        y1 = self.c_bond.y1 * 100 + offsety
        y2 = self.c_bond.y2 * 100 + offsety
        dx = x2 - x1
        dy = y2 - y1
        len = math.sqrt(dx**2 + dy**2)
        ux = dx / len
        uy = dy / len
        x1a = x1 + 10 * uy - 0.5 * ux
        y1a = y1 - 10 * ux - 0.5 * uy
        x1b = x1 - 10 * uy - 0.5 * ux
        y1b = y1 + 10 * ux - 0.5 * uy
        x2a = x2 + 10 * uy + 0.5 * ux
        y2a = y2 - 10 * ux + 0.5 * uy
        x2b = x2 - 10 * uy + 0.5 * ux
        y2b = y2 + 10 * ux + 0.5 * uy
        return f'  <polygon points="{x1a:.2f},{y1a:.2f} {x1b:.2f},{y1b:.2f} {x2b:.2f},{y2b:.2f} {x2a:.2f},{y2a:.2f}" fill="green"/>\n'

#Create a Molecule class that is a subclass of the molecule class.   
class Molecule(molecule.molecule):
    
    #Create a __str__ method that returns a string with the atoms and bonds.
    def str(self):
        out = "Atoms:\n"
        for i in range(self.atom_no):
            out += str(self.get_atom(i))+ "\n"
        out += "Bonds:\n"
        for i in range(self.bond_no):
            out + str(self.get_bond(i)) + "\n"
        return out

    #Create a svg method that returns a string with the atoms and bonds.
    def svg(self):
        svg = header
        atomNum = 0
        bondNum = 0

        while atomNum < self.atom_no and bondNum < self.bond_no:

            a1 = Atom(self.get_atom(atomNum))
            b1 = Bond(self.get_bond(bondNum))

            if a1.z < b1.z:
                svg += a1.svg()
                atomNum += 1
            else:
                svg += b1.svg()
                bondNum += 1


        while atomNum < self.atom_no:
            a1 = Atom(self.get_atom(atomNum))
            svg += a1.svg()
            atomNum += 1

        while bondNum < self.bond_no:
            b1 = Bond(self.get_bond(bondNum))
            svg += b1.svg()
            bondNum += 1


        svg += footer
        return svg

    #Create a parse method that parses the SDF file.
    def parse(self, file):
        sdf_lines = file.readlines()

        num_atoms = int(sdf_lines[3].split()[0])
        num_bonds = int(sdf_lines[3].split()[1])

        for i in range(num_atoms):
            line = sdf_lines[i+4]
            x, y, z, symbol= line.split()[:4]
            self.append_atom(symbol, float(x), float(y), float(z))


        for i in range(num_bonds):
            line = sdf_lines[i + num_atoms + 4]
            atom1, atom2, bond_type = line.split()[:3]
            self.append_bond(int(atom1), int(atom2), int(bond_type))


        