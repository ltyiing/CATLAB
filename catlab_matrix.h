#ifndef __CATLAB_MATRIX_H__
#define __CATLAB_MATRIX_H__
#include <catlab_util.h>
#include <stdio.h>
#include <umfpack.h>

#define CAT_SYM         0x00000001
#define CAT_HER         0x00000002
#define CAT_PDM         0x00000004
#define CAT_GEM         0x00000008
#define CAT_GBM         0x00000010
#define CAT_TRM         0x00000020
#define CAT_CSR         0x00000100
#define CAT_CSC         0x00000200
#define CAT_COO         0x00000400
#define CAT_DIA         0x00000800
#define CAT_BSR         0x00001000
#define CAT_SKY         0x00002000

#define CAT_MATRIX_PRINT(x)  cat_matrix_fprint(stdout, (ptr_cat_mat)x)
#define CAT_MATRIX_FPRINT(fp,x)  cat_matrix_fprint(fp, (ptr_cat_mat)x)
#define CAT_MATRIX_DESTRUCTOR(x) cat_matrixDestructor((ptr_cat_mat*)x);
#define CAT_MATRIX_DUPLICATE(x) cat_matrixDuplicate((ptr_cat_mat)x)
#define CAT_VECZ_PRINT(x,itr,n) for (itr=0;itr<n;itr++) printf("(%g,%g)\n",CAT_REAL(x[itr]),CAT_IMAG(x[itr]));
#define CAT_VEC_PRINT(x,itr,n) for (itr=0;itr<n;itr++) printf("%g\n",x[itr]);

#define CAT_UMFPACK_DI  0x00000001
#define CAT_UMFPACK_ZI  0x00000010

typedef struct _tagCatWorkspace {
    double Control[UMFPACK_CONTROL];
    double Info[UMFPACK_INFO];
    void   *Symbolic;
    void   *Numeric;
    int    isreuse;
    int    umftype;
} cat_workspace, *ptr_cat_workspace;

typedef struct _tagCatMatrix {
    void                    *data;
    int                     lshape;
    int                     *shape;
    int                     ldata;
    cat_flag                datatype;
    cat_bool                bPrepared;
    cat_flag                matrixtype;
    int                     ku;
    int                     kl;
    int                     *ptrind1;
    int                     *ptrind2;
} cat_mat, *ptr_cat_mat;

typedef struct _tagCatSMatrix {
    float                   *data;
    int                     lshape;
    int                     *shape;
    int                     ldata;
    cat_flag                datatype;
    cat_bool                bPrepared;
    cat_flag                matrixtype;
    int                     ku;
    int                     kl;
    int                     *ptrind1;
    int                     *ptrind2;
} cat_smat, *ptr_cat_smat;

typedef struct _tagCatDMatrix {
    double                  *data;
    int                     lshape;
    int                     *shape;
    int                     ldata;
    cat_flag                datatype;
    cat_bool                bPrepared;
    cat_flag                matrixtype;
    int                     ku;
    int                     kl;
    int                     *ptrind1;
    int                     *ptrind2;
} cat_dmat, *ptr_cat_dmat;

typedef struct _tagCatCMatrix {
    float _Complex          *data;
    int                     lshape;
    int                     *shape;
    int                     ldata;
    cat_flag                datatype;
    cat_bool                bPrepared;
    cat_flag                matrixtype;
    int                     ku;
    int                     kl;
    int                     *ptrind1;
    int                     *ptrind2;
} cat_cmat, *ptr_cat_cmat;

typedef struct _tagCatZMatrix {
    double _Complex         *data;
    int                     lshape;
    int                     *shape;
    int                     ldata;
    cat_flag                datatype;
    cat_bool                bPrepared;
    cat_flag                matrixtype;
    int                     ku;
    int                     kl;
    int                     *ptrind1;
    int                     *ptrind2;
} cat_zmat, *ptr_cat_zmat;

void cat_zvec_add(ptr_cat_zmat vec, double _Complex addnum);
void cat_zvec_absmin_index(ptr_cat_zmat vec, int* ptrindex);

ptr_cat_mat cat_EmptyMatConstructor();
void cat_zmat_gbm_AXPBY(double _Complex a, ptr_cat_zmat matx,
                double _Complex b, ptr_cat_zmat maty);
void cat_zmat_gbm_Adjust(ptr_cat_zmat pmat, int newku, int newkl);
void cat_zmat_SCALE(ptr_cat_zmat pmat, double _Complex alpha);
void cat_zmat_csc_AXPBY(double _Complex a, ptr_cat_zmat matx,
            double _Complex b, ptr_cat_zmat maty);
void cat_zmat_matrixCC2GE(ptr_cat_zmat tmat);

void cat_zmat_gem_AXPBY(double _Complex a, ptr_cat_zmat matx,
                double _Complex b, ptr_cat_zmat maty);

ptr_cat_mat cat_CSCMatConstructor(cat_flag matdatatype, int row, int col, 
            int* ai, int* aj, void* av);
/***********************************************************************/
//routines like sparse blas
void              cat_zcscaxpby(int m, const void* alpha,
                        const cat_z *x, const int *ix, const int *jx,
                        const void* beta, cat_z **y, int **iy, int** jy);
//sparse blas part, if MKL is used, it'll be redirect to mkl
void              cat_zcscgemv(CBLAS_TRANSPOSE TransA, int m,
                        const cat_z *a, const int *ia, const int *ja,
                        const cat_z *x, cat_z* y);
/***********************************************************************/

ptr_cat_workspace cat_mat_csc_mldivide_alloc();
void              cat_mat_csc_mldivide_dealloc(ptr_cat_workspace psp);
void              cat_matz_csc_mldivide(ptr_cat_zmat matA, cat_z* ivec,
                        cat_z* ovec, ptr_cat_workspace pworkspace);

ptr_cat_mat cat_matrixDuplicate(ptr_cat_mat smat);
ptr_cat_mat cat_GMatConstructor(cat_flag matdatatype, int dimension, int* shape);
ptr_cat_mat cat_BMatConstructor(cat_flag matdatatype, int rol, int col, int ku, int kl);
void        cat_matrixDestructor(cat_mat **pptrmat);
void        cat_matrixD2Z(ptr_cat_dmat tmat);
void        cat_matrixZ2DReal(ptr_cat_zmat tmat);
void        cat_matrixZ2DImag(ptr_cat_zmat tmat);
void        cat_zmat_matrixGE2CC(ptr_cat_zmat tmat);
void        cat_zmat_matrixGB2CC(ptr_cat_zmat tmat);
void        cat_zmat_matrixGB2GE(ptr_cat_zmat tmat);
void        cat_dmat_matrixGB2GE(ptr_cat_dmat tmat);

ptr_cat_zmat cat_zmat_matrixCombineCC2GE(int nrow, int ncol, ptr_cat_zmat *ptrmat);
ptr_cat_dmat cat_GmatRealZ(ptr_cat_zmat tmat);
ptr_cat_dmat cat_GmatImagZ(ptr_cat_zmat tmat);
ptr_cat_zmat cat_matz_BMat_Eye(int n);
void cat_zmat_GMatMultVec(ptr_cat_zmat pmat, cat_z* ivec, cat_z* ovec);
void cat_dmat_GMatMultVec(ptr_cat_dmat pmat, cat_d* ivec, cat_d* ovec);
void cat_mat_GMatMultVec(ptr_cat_mat pmat, void* ivec, void* ovec);
void cat_zmat_BMatMultVec(ptr_cat_zmat pmat, cat_z* ivec, cat_z* ovec);
void cat_dmat_BMatMultVec(ptr_cat_dmat pmat, double* ivec, double* ovec);
void cat_mat_BMatMultVec(ptr_cat_mat pmat, void* ivec, void* ovec);
void cat_mat_MatMultVec(ptr_cat_mat pmat, void* ivec, void* ovec);

void cat_matrix_fprint_s_1d(FILE* fp, ptr_cat_smat smat);
void cat_matrix_fprint_d_1d(FILE* fp, ptr_cat_dmat smat);
void cat_matrix_fprint_c_1d(FILE* fp, ptr_cat_cmat smat);
void cat_matrix_fprint_z_1d(FILE* fp, ptr_cat_zmat smat);
void cat_matrix_fprint_s_2d(FILE* fp, ptr_cat_smat smat);
void cat_matrix_fprint_d_2d(FILE* fp, ptr_cat_dmat smat);
void cat_matrix_fprint_c_2d(FILE* fp, ptr_cat_cmat smat);
void cat_matrix_fprint_z_2d(FILE* fp, ptr_cat_zmat smat);
void cat_matrix_fprint(FILE* fp, ptr_cat_mat smat);
void cat_matrix_fwrite_z_2d(FILE *fp, ptr_cat_zmat smat);
void cat_matrix_fwrite_z_1d(FILE *fp, ptr_cat_zmat smat);
void cat_matrix_filenamewrite_z_2d(char* filename, ptr_cat_zmat smat);
void cat_matrix_filenamewrite_z_1d(char* filename, ptr_cat_zmat smat);
#endif//__CATLAB_MATRIX_H__
