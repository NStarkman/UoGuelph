#include "mol.h" 
/**
 * Author: Nathan Starkman
 * Date: 2023-02-27
 * Assignment: A3
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
 * This function takes a pointer to a bond structure, two pointers to atom structures, and a pointer to an unsigned char.
 */
void bondset( bond *bond, unsigned short *a1, unsigned short *a2, atom **atoms, unsigned char *epairs ){
    bond->a1 = *a1;
    bond->a2 = *a2;
    bond->epairs = *epairs;
    bond->atoms = *atoms;
  // Compute the coordinates of the bond
    compute_coords(bond);
}

/**
 * This function copies the values of the bond structure into the variables passed to the function.
 */
void bondget(bond *bond, unsigned short *a1, unsigned short *a2, atom **atoms, unsigned char *epairs) {
  // Get the values from the bond structure
  *a1 = bond->a1;
  *a2 = bond->a2;
  *atoms = bond->atoms;
  *epairs = bond->epairs;
}

/**
 * This function takes a pointer to a bond structure, and computes the coordinates of the bond.
 */
void compute_coords(bond *bond) {
    atom *a1 = &bond->atoms[bond->a1];
    atom *a2 = &bond->atoms[bond->a2];

    bond->x1 = a1->x;
    bond->y1 = a1->y;
    bond->x2 = a2->x;
    bond->y2 = a2->y;
    bond->z = (a1->z + a2->z) / 2.0;

    double dx = bond->x2 - bond->x1;
    double dy = bond->y2 - bond->y1;
    bond->len = sqrt(dx * dx + dy * dy);
    bond->dx = dx / bond->len;
    bond->dy = dy / bond->len;
}


/**
 * This function allocates memory for a molecule structure, and all the arrays that are part of the molecule
 * structure. It returns a pointer to the molecule structure.
 */
molecule *molmalloc(unsigned short atom_max, unsigned short bond_max) {
    molecule *mol = malloc(sizeof(molecule));
    if (mol == NULL){
        return NULL;
    }
    mol->atom_max = atom_max;
    mol->atom_no = 0;
    mol->atoms = malloc(sizeof(atom) * atom_max);
    if (mol->atoms == NULL){
        return NULL;
    }
    memset(mol->atoms, 0, sizeof(atom) * atom_max);
    mol->atom_ptrs = malloc(sizeof(atom *) * atom_max);
    if (mol->atom_ptrs == NULL){
        return NULL;
    }
    memset(mol->atom_ptrs, 0, sizeof(atom *) * atom_max);
    mol->bond_max = bond_max;
    mol->bond_no = 0;
    mol->bonds = malloc(sizeof(bond) * bond_max);
    if (mol->bonds == NULL){
        return NULL;
    }
    memset(mol->bonds, 0, sizeof(bond) * bond_max);
    mol->bond_ptrs = malloc(sizeof(bond *) * bond_max);
    if (mol->bond_ptrs == NULL){
        return NULL;
    }
    memset(mol->bond_ptrs, 0, sizeof(bond *) * bond_max);
    return mol;
}

/**
 * This function takes a molecule and returns a copy of it
 */
molecule *molcopy(molecule *src) {
    molecule * mol = molmalloc(src->atom_max, src->bond_max);
    if (mol == NULL) {
        return NULL;
    }

    for (int i = 0; i < src->atom_no; i++) {
        molappend_atom(mol, src->atoms);
    }
    for (int i = 0; i < src->bond_no; i++) {
        molappend_bond(mol, src->bonds);
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
    //molsort(molecule);
}

/**
 * This function takes a pointer to a molecule and a pointer to a bond, and appends the bond to the molecule
*/
void molappend_bond(molecule *molecule, bond *bond) {
    if (molecule->bond_max ==0){
        molecule->bond_max = 1;
        molecule->bonds = realloc(molecule->bonds, sizeof(struct bond) * molecule->bond_max);
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
    bondset(&molecule->bonds[molecule->bond_no], &bond->a1, &bond->a2, &bond->atoms, &bond->epairs);
    molecule->bond_ptrs[molecule->bond_no] = &molecule->bonds[molecule->bond_no];
    molecule->bond_no++;
}


/**
 * The function `atomcmp` compares two atoms by their element number. The function `bondcmp` compares
 * two bonds by the average z-coordinate of the two atoms in the bond
 */
int bondcmp(const void *a, const void *b) {
    bond *bondA, *bondB;

    // Convert to atom (from void*) and derefernce address
    bondA = *(struct bond**)a;
    bondB = *(struct bond**)b;

    // Compare
    if (bondA->z < bondB->z) { // A goes before B
        return -1;
    } else if (bondA->z > bondB->z) { // A goes after B
        return 1;
    } else {
        return 0;
    }
}

int atomcmp(const void* atomA_void, const void* atomB_void) {
    atom *atomA, *atomB;

    // Convert to atom (from void*) and derefernce address
    atomA = *(struct atom**)atomA_void;
    atomB = *(struct atom**)atomB_void;

    // Compare
    if (atomA->z < atomB->z) { // A goes before B
        return -1;
    } else if (atomA->z > atomB->z) { // A goes after B
        return 1;
    } else {
        return 0;
    }
}

/**
 * It sorts the atom and bond pointers in a molecule by element number and average z-coordinate respectively
 */
void molsort(molecule *molecule) {
    
   
    qsort(molecule->atom_ptrs, molecule->atom_no, sizeof( atom*), atomcmp);
    qsort(molecule->bond_ptrs, molecule->bond_no, sizeof( bond*), bondcmp);
       
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
 * It takes a 3x3 matrix and a 3x3 matrix and sets the first matrix to the product of the two matrices
 */
void mol_xform(molecule *mol, xform_matrix xform) {
  int num_bonds = mol->bond_no;
  bond *bonds = mol->bonds;
  
  // Apply the transformation matrix to each atom in the molecule
  for (int i = 0; i < mol->atom_no; i++) {
    double x = mol->atoms[i].x;
    double y = mol->atoms[i].y;
    double z = mol->atoms[i].z;
    
    mol->atoms[i].x = xform[0][0] * x + xform[0][1] * y + xform[0][2] * z;
    mol->atoms[i].y = xform[1][0] * x + xform[1][1] * y + xform[1][2] * z;
    mol->atoms[i].z = xform[2][0] * x + xform[2][1] * y + xform[2][2] * z;
  }
  
  for (int i = 0; i < num_bonds; i++) {
    bond *bond = &bonds[i];
    compute_coords(bond);
    
    bond->x1 = xform[0][0] * bond->x1 + xform[0][1] * bond->y1 + xform[0][2] * bond->z;
    bond->y1 = xform[1][0] * bond->x1 + xform[1][1] * bond->y1 + xform[1][2] * bond->z;
    bond->x2 = xform[0][0] * bond->x2 + xform[0][1] * bond->y2 + xform[0][2] * bond->z;
    bond->y2 = xform[1][0] * bond->x2 + xform[1][1] * bond->y2 + xform[1][2] * bond->z;
  }
}
