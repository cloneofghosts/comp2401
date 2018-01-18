#include <stdio.h>
#include <string.h>

#define MAX_BUF 16
#define MAX_STR 64

typedef struct{

  char          markingComponent[MAX_BUF][MAX_STR];
  int           numComponents;
  unsigned char weightingScheme[MAX_BUF][MAX_BUF];
  int           numSchemes;

} WeightType;

void initComponents(WeightType*);
void initSchemes(WeightType*);
void computeGrades(WeightType*, float*);

int main(){

  WeightType weightingScheme;
  int        i;
  float      marks[MAX_BUF];

  //asks the user for the number of components
  printf("How many marking components? ");
  scanf("%d", &weightingScheme.numComponents);
  
  initComponents(&weightingScheme);

  //asks user for the number of weighting schemes
  printf("\nEnter number of weighting schemes: ");
  scanf("%d", &weightingScheme.numSchemes);

  initSchemes(&weightingScheme);

  printf("\n");
  
  //asks user to inputs grades in the same order as they entered in components
  for(i=0; i<weightingScheme.numComponents; i++){
    printf("Enter your %s mark: ", weightingScheme.markingComponent[i]);
    scanf("%f", &marks[i]);
  }

  computeGrades(&weightingScheme, marks);
 
  printf("\n");
  return 0;
}

/*
  Function:  initComponents
  Purpose:   To initilize the names of the Marking Components in the marking component array
       in:   the address of the weighting scheme structure
      out:   the new weighting scheme with data for the components of the weighting scheme
 */

void initComponents(WeightType *scheme){

  int i;
  
  for(i=0; i<scheme->numComponents; i++){
    printf("  enter component name: ");
    scanf("%s", scheme->markingComponent[i]);
  }
  
}

/*
  Function:  initSchemes
  Purpose:   To initilize the weighting scheme array with component weights in the order that the user entered in the components
  in:   the address of the weighting scheme structure
  out:   the new weighting scheme structure with data for the different weighting schemes
*/

void initSchemes(WeightType *scheme){

  int           i, j;
  unsigned char totalWeight;
  
  for(i=0; i<scheme->numSchemes; i++){
    printf("Marking Scheme #%d:\n", i+1);
    totalWeight = 0;
    for(j=0; j<scheme->numComponents; j++){
      printf("  enter %s weight: ", scheme->markingComponent[j]);
      scanf("%hhu", &scheme->weightingScheme[i][j]);
      totalWeight += scheme->weightingScheme[i][j];
    }
    /*
      Makes sure that the total weight entered is exactly 100
      If the marks are not 100, decreases the value of i so that the user can re-input the weights
    */
    if(totalWeight != 100){
      printf("values do not add up to exactly 100! Please try again...\n");
      i--;
    }
    printf("\n");
  } 
}

/*
  Function:  computeGrades
  Purpose:   To compute the final marks using each weighting scheme
       in:   the address of the weighting scheme structure
       in:   the address of the marks to be computed using the weighting scheme
 */

void computeGrades(WeightType *scheme, float *marks){

  int   i, j;
  float finalMark;

  for(i=0; i<scheme->numSchemes; i++){
    finalMark = 0;
    printf("\nGrade using marking scheme #%d: ", i+1);
    for(j=0; j<scheme->numComponents; j++){
      finalMark += marks[j] * scheme->weightingScheme[i][j];
    }
    printf("%.2f", finalMark/100);
  }
}
