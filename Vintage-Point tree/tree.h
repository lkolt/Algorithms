#pragma once


////////////////////////////////////////////////////////////////
// Global Definitions
////////////////////////////////////////////////////////////////


#define _NUM_PT_RANDOM_SUBSET	1000	// Minimum number of points in Random subset
#define _NUM_CAND_VP		100	// Number of candidate VPs

#define _DEFAULT_BRANCH		2	// Branching factor of the vp-tree (must > 1)

#define _MAX_POINTS_NODE	10	// Maximum number of points in a node
#define _MIN_POINTS_NODE	1	// Minimum number of points in a node

#define _VPTREE_ID		"VPTREE-FILE"
#define _VPTREE_LEAF		"LEAF"
#define _VPTREE_INTERNAL	"INTERNAL"

#define _LARGE_VALUE		9999999


////////////////////////////////////////////////////////////////
// Data Structure
////////////////////////////////////////////////////////////////


typedef struct
{
	int  nPoints;
	int  dimension;

	double *points;		// size : numPoints * dimension

} DataSet;


typedef struct VPNodeStru
{
	int isLeaf;			// _TRUE or _FALSE

	struct VPNodeStru **child;	// children (array of numBranch pointers)
	double *medians;		// array of (numBranch-1) distances 
							// separating each group such that the
							// (i)th group is bounded by medians[i]

	int nPoints;		// number of data points

	double *points;		// if (isLeaf)
						//    this is the data points
						// else
						//    this is the vantage Point(s)
						//    (note that vp is also data point)

	int *dataID;		// dataIDs' keep track of where the 
						// points goes in the VP tree

} VPNode;


typedef struct
{
	int numBranch;
	int dimension;

	VPNode *root;

} VPTree;


///////////////////////////////////////////////////////////////////////
//  
//  General Definition
//

#define _MAX_BUF_SIZE	255
#define _MAX_STR_SIZE	255
#define _MAX_PATH_SIZE	255

#define _OKAY		1
#define _ERROR		-1
#define _TRUE		1
#define _FALSE		0

#define _EPSILON	1e-7

#define TWO_PI (2.0*M_PI)
#define HALF_PI (0.5*M_PI)

#define toDegree(X)     ((X)*180.0/M_PI)
#define toRadian(X)     ((X)*M_PI/180.0)

#define errexit(msg)		{ printf(msg);           exit(1); }
#define errexit2(msg,arg1)	{ printf(msg,arg1);      exit(1); }
#define errexit3(msg,arg1,arg2)	{ printf(msg,arg1,arg2); exit(1); }

#define max(x,y)		( (x) > (y) ? (x) : (y) )
#define min(x,y)		( (x) < (y) ? (x) : (y) )

#define toggle(bool)		( (bool) == _TRUE ? _FALSE : _TRUE )

///////////////////////////////////////////////////////////////////////
// All Path Information should reference to _TOP_DIR

#define _TOP_DIR	"/nfs/italy/home/cwfu/research/vpnav/"


void
bubbleSortByIndex(int **sortList, double *value, int nTri);

void
mySwap(int *D, double *comp, int x, int i);

void
q_sort(int *D, double *comp, int low, int high, int size);

DataSet *
readDataSet(int n, int dim, char *dataFile);

double
sqrDist(double *p1, double *p2, int dim);

VPTree *
buildVPTree(DataSet *dataSet, int numBranch);

VPNode *
readVPNode(FILE *fp, int numBranch, int dimension, int *nPoints);

VPTree *
readVPTree(char *treeFile, int *nPoints);

int
writeVPNode(FILE *fp, VPNode *vpNode, int numBranch, int dimension);

int
writeVPTree(char *treeFile, VPTree *vpTree);

int
searchKNNVPNode(VPNode *vpNode, double *queryPt,
	double *kMinDist, double *resultPt, int *resultID,
	int numBranch, int dimension, int k);


int
knnsearch(VPTree *vpTree, double *queryPt, int k,
	double *resultPt, int *resultID);


void
freeDataSet(DataSet *dataSet);

void
freeVPNode(VPNode *vpNode, int numBranch);

void
freeVPTree(VPTree *vpTree);

void
printPt(FILE *out, double *pt, int dim);

int build(int sz, char **args);


void readQuery(char *queryFile, double **queryPt, int dimension);


int search(int sz, char **args);

int trytree(int argc, char **argv);