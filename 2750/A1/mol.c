#include "mol.h" 
/**
 * Author: Nathan Starkman
 * Date: 2023-01-30
 * Assignment: A1
 * Course: CIS*2750
 * Description: This file contains the functions for the molecule structure 
*/

/**
 * This function takes a pointer to an atom structure, a string, and three doubles, and sets the atom's element,
 * x, y, and z values to the string and doubles
 */
void atomset(atom *atom, char element[3], double *x, double *y, double *z){
    strcpy(atom->element, element);
    atom->x = *x;
    atom->y = *y;
    atom->z = *z;
}

/**
 * This function copies the values of the atom structure into the variables passed to the function.
 */
void atomget(atom *atom, char element[3], double *x, double *y, double *z){
    strcpy(element, atom->element);
    *x = atom->x;
    *y = atom->y;
    *z = atom->z;
}

/**
 * This function takes a pointer to a bond, two pointers to atoms, and an unsigned char, and sets the bond's a1,
 * a2, and epairs fields to the atom pointers and the unsigned char
 */
void bondset(bond *bond, atom *a1, atom *a2, unsigned char epairs){
    bond->a1 = a1;
    bond->a2 = a2;
    bond->epairs = epairs;
}

/**
 * This function returns the two atoms and the number of electron pairs in a bond.
 */
void bondget(bond *bond, atom **a1, atom **a2, unsigned char *epairs){
    *a1 = bond->a1;
    *a2 = bond->a2;
    *epairs = bond->epairs;
}

/**
 * This function allocates memory for a molecule structure, and all the arrays that are part of the molecule
 * structure. It returns a pointer to the molecule structure.
 */

molecule *molmalloc(unsigned short atom_max, unsigned short bond_max){
    molecule *mol;
    mol = malloc(sizeof(struct molecule));
    mol->atom_max = atom_max;
    mol->atom_no = 0;
    mol->atoms = malloc(sizeof(struct atom) * atom_max);
    mol->atom_ptrs = malloc(sizeof(struct atom *) * atom_max);
    mol->bond_max = bond_max;
    mol->bond_no = 0;
    mol->bonds = malloc(sizeof(struct bond) * bond_max);
    mol->bond_ptrs = malloc(sizeof(struct bond *) * bond_max);
    return mol;
}


/**
 * This function takes a molecule and returns a copy of it
 */

molecule *molcopy(molecule *src){
    molecule *mol = molmalloc(src->atom_max, src->bond_max);
    for(int i = 0; i < src->atom_no; i++){
        molappend_atom(mol, src->atom_ptrs[i]);
    }
    for(int i = 0; i < src->bond_no; i++){
        molappend_bond(mol, src->bond_ptrs[i]);
    }
    return mol;
}


/**
 * This function frees the memory allocated to a molecule structure
 */
void molfree(molecule *ptr){
    free(ptr->atoms);
    free(ptr->atom_ptrs);
    free(ptr->bonds);
    free(ptr->bond_ptrs);
    free(ptr);
}

/**
 * This function takes a pointer to a molecule and a pointer to an atom, and appends the atom to the molecule
 */
void molappend_atom(molecule *molecule, atom *atom){
    if (molecule->atom_max==0){
        molecule->atom_max = 1;
        molecule->atoms = realloc(molecule->atoms, sizeof(struct atom) * molecule->atom_max) ;
        molecule->atom_ptrs = realloc(molecule->atom_ptrs, sizeof(struct atom *) * molecule->atom_max);
    }
    else if (molecule->atom_no >= molecule->atom_max){
        molecule->atom_max *= 2;
        molecule->atoms = realloc(molecule->atoms, sizeof(struct atom) * molecule->atom_max);
        molecule->atom_ptrs = realloc(molecule->atom_ptrs, sizeof(struct atom *) * molecule->atom_max);
        for (int i = 0;i<molecule->atom_no; i++){
            molecule->atom_ptrs[i] = &molecule->atoms[i];
        }
        
    }
    atomset(&molecule->atoms[molecule->atom_no], atom->element, &atom->x, &atom->y, &atom->z);
    molecule->atom_ptrs[molecule->atom_no] = &molecule->atoms[molecule->atom_no];        
    molecule->atom_no++;
    molsort(molecule);
}
/**
 * This function takes a pointer to a molecule and a pointer to a bond, and appends the bond to the molecule
*/
void molappend_bond(molecule *molecule, bond *bond){
    if (molecule->bond_max==0){
        molecule->bond_max = 1;
        molecule->bonds = realloc(molecule->bonds, sizeof(struct bond) * molecule->bond_max) ;
        molecule->bond_ptrs = realloc(molecule->bond_ptrs, sizeof(struct bond *) * molecule->bond_max);
    }
    else if (molecule->bond_no >= molecule->bond_max){
        molecule->bond_max *= 2;
        molecule->bonds = realloc(molecule->bonds, sizeof(struct bond) * molecule->bond_max);
        molecule->bond_ptrs = realloc(molecule->bond_ptrs, sizeof(struct bond *) * molecule->bond_max);
        for (int i = 0;i<molecule->bond_no; i++){
            molecule->bond_ptrs[i] = &molecule->bonds[i];
        }
    }
    bondset(&molecule->bonds[molecule->bond_no], bond->a1, bond->a2, bond->epairs);
    molecule->bond_ptrs[molecule->bond_no] = &molecule->bonds[molecule->bond_no];
    molecule->bond_no++;
    molsort(molecule);
}

/**
 * The function `atomcmp` compares two atoms by their element number. The function `bondcmp` compares
 * two bonds by the average z-coordinate of the two atoms in the bond
 */
int atomcmp(const void *a, const void *b){
    atom *a1 = *(atom **)a;
    atom *a2 = *(atom **)b;
    return (a1->element - a2->element);
}
int bondcmp(const void *a, const void *b){
    bond *b1 = *(bond **)a;
    bond *b2 = *(bond **)b;
    double z1 = (b1->a1->z + b1->a2->z)/2;
    double z2 = (b2->a1->z + b2->a2->z)/2;
    return z1-z2;
}

/**
 * It sorts the atom and bond pointers in a molecule by element number and average z-coordinate respectively
 */
void molsort(molecule *molecule){
    qsort(molecule->atom_ptrs, molecule->atom_no, sizeof(atom *), atomcmp);
    qsort(molecule->bond_ptrs, molecule->bond_no, sizeof(bond *), bondcmp);
}


/**
 * It takes a 3x3 matrix and a degree value and sets the matrix to a rotation matrix that rotates
 * around the x axis by the given degree value
 */
void xrotation(xform_matrix xform, unsigned short deg) {
    double rad = deg * 3.1415926535 / 180.0;
    xform[0][0] = 1;
    xform[0][1] = 0;
    xform[0][2] = 0;
    xform[1][0] = 0;
    xform[1][1] = cos(rad);
    xform[1][2] = -sin(rad);
    xform[2][0] = 0;
    xform[2][1] = sin(rad);
    xform[2][2] = cos(rad);
}

/**
 * It takes a 3x3 matrix and a degree value and sets the matrix to a rotation matrix that rotates
 * around the y axis by the given degree value
 */
void yrotation(xform_matrix xform, unsigned short deg) {
    double num = deg * 3.1415926535 / 180.0;
    double array[3][3] = {{cos(num),0,sin(num)},{0,1,0},{-sin(num),0,cos(num)}};
    xform[0][0]=array[0][0];
    xform[0][1]=array[0][1];
    xform[0][2]=array[0][2];
    xform[1][0]=array[1][0];
    xform[1][1]=array[1][1];
    xform[1][2]=array[1][2];
    xform[2][0]=array[2][0];
    xform[2][1]=array[2][1];
    xform[2][2]=array[2][2];
}

/**
 * It takes a 3x3 matrix and a degree value and sets the matrix to a rotation matrix that rotates
 * around the z axis by the given degree value
 */
void zrotation(xform_matrix xform, unsigned short deg) {
    double num=deg*3.1415926535/180.0;
    xform[0][0]=cos(num);
    xform[0][1]=-sin(num);
    xform[0][2]=0;
    xform[1][0]=sin(num);
    xform[1][1]= cos(num);
    xform[1][2] = 0;
    xform[2][0] = 0;
    xform[2][1] = 0;
    xform[2][2] = 1;
}

/**
 * This function takes a molecule and a transformation matrix and applies the transformation to the molecule
 */
void mol_xform(molecule* mol, xform_matrix xform) {
    for (int i = 0; i < mol->atom_no; i++) {
        double x = mol->atoms[i].x;
        double y = mol->atoms[i].y;
        double z = mol->atoms[i].z;
        mol->atoms[i].x = xform[0][0] * x + xform[0][1] * y + xform[0][2] * z;
        mol->atoms[i].y = xform[1][0] * x + xform[1][1] * y + xform[1][2] * z;
        mol->atoms[i].z = xform[2][0] * x + xform[2][1] * y + xform[2][2] * z;
    }
}
