// LAB 2 - COP 3502 - Spring 23
// Author Name: Sebastian Ferreira

/*
In this program we are working with a dynamic memory allocation coding problem. In this program, we will read a set of students data and their grading information and then process them 
and then print the requested information. 
*/ 

// pre processor directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"
// represents the the max size that student name can be +1 for null character terminator
#define NAMEMAX 51
#define studentAccess courses[cn][sn]

// Student struct
typedef struct student 
{ 
  // this is a pointer that will store the last name for the student
  char *lname; //this will require DMA to store a string 

  // variable declaration that will hold the students data i.e., assignments and grades
  int assignment; 
  int finalExam; 
  int total; 

  // this is a pointer that will hold the number of quizzes 
  int *quizzes;//this will require DMA to store quizzes 
}student;  

// function prototypes
student **readCourses(int *C, int *N, int *M);
void printHighestTotal(student **courses, int C, int N, int M);
void release_memory(student **st, int C, int N, int M);

student **readCourses(int *C, int *N, int *M)
{
  student** courses;
  char lname[NAMEMAX];
  int i, j; 

  // scan the amount of courses students and quizzes
  scanf("%d %d %d", C, N, M);

  courses = (student**)malloc(*C * sizeof(student*));

  // course number, student number, quiz number
  int cn, sn, qn;

  // this allocates mem for the list of students for each course
  for(cn = 0; cn < *C; cn++){

    // allocate array of students for cnth course
    courses[cn] = malloc(*N * sizeof(student));

    // now access each students of course[cn]
    for(sn = 0; sn < *N; sn++){
      
      // total for the student
      int total = 0;
      
      // read name and get the length of the name
      scanf("%s", lname);
      int length = strlen(lname) + 1;
      courses[cn][sn].lname = malloc(length * sizeof(char));
      strcpy(studentAccess.lname, lname);
      
      // take assignment score
      scanf("%d", &studentAccess.assignment);
      total += studentAccess.assignment;
      
      // allocate mem for M number of quizzes for that particular student
      studentAccess.quizzes = malloc(*M * sizeof(int));

      // take all the quiz scores
      for(qn = 0; qn < *M; qn++){
        scanf("%d", &studentAccess.quizzes[qn]);
        total += studentAccess.quizzes[qn];
      }
      
      // take the final exam score from user input
      scanf("%d", &studentAccess.finalExam);
      total += studentAccess.finalExam;

      // store the total
      studentAccess.total = total;
    }
  }
  // returns the entire 2D array with the filled up data
  return courses;
}

void printHighestTotal(student **courses, int C, int N, int M)
{
  int maxStudentIDX, maxCourseIDX = 0;
    float max = -1;

  int cn, sn, qn;

    // loop through all the courses
  for(int cn = 0; cn < C; cn++)
  {
    // loop through all the students in the current course
    for(int sn = 0; sn < N; sn++)
    {
      // if the current student has a higher total than the max, then update the max
      if(studentAccess.total > max)
      {
        max = studentAccess.total;
        maxCourseIDX = cn;
        maxStudentIDX = sn;
      }
    }
  }

  // print out the student with the highest total and their total
  printf("Name: %s\nAssignment: %d\nQuizzes: ", courses[maxCourseIDX][maxStudentIDX].lname, courses[maxCourseIDX][maxStudentIDX].assignment);

  for(int qn = 0; qn < M; qn++){
    printf("%d ", courses[maxCourseIDX][maxStudentIDX].quizzes[qn]);
  }

  printf("\nFinal exam: %d\nTotal: %d\nCourse number: %d",courses[maxCourseIDX][maxStudentIDX].finalExam, courses[maxCourseIDX][maxStudentIDX].total, C-1);

  // courses[maxCourseIDX][maxStudentIDX].quizzes[i]
  
  /*
    // iterate over the courses 
  for(int i = 0; i < C; i++){
    for(int j = 0; j < N; j++){
        if(courses[i]->total > max){
          max = courses[i]->total;
        }
      }
  }
  
  for(int i = 0; i < C; i++){
    if(courses[i]->total > max){
      max = courses[i]->total;
      maxStudentIDX = i;
    }
  }
  */
      // iterate over the students
        // if the current student has a total hgigher than the one already in maxVal update all your              variables

    // print the name then the assignment and then the quizzes and grades both to the console and to the      terminal
    /*printf("Name: %s\n", courses[maxCourseIDX][maxStudentIDX].lname);
    printf("Assignment: %d\n", courses[maxCourseIDX][maxStudentIDX].assignment);

    printf("Quizzes: ");
    for (int q = 0; q < M; q++)
    {
        printf("%d", courses[maxCourseIDX][maxStudentIDX].quizzes[M]);
    }

    printf("\nFinal Exam: %d\n", courses[maxCourseIDX][maxStudentIDX].finalExam);
    printf("Total: %d\n", courses[maxCourseIDX][maxStudentIDX].total);
  */
}

void release_memory(student **st, int C, int N, int M)
{
  // strategy: free the most inner elements first then backtrack to free the containers

  // we need to release the quizzes and lastnames for each student then release students and finally     courses
  for(int cn = 0; cn < C; cn++)
    {
      for(int sn = 0; sn < N; sn++)
        {
          free(st[cn][sn].lname);
          free(st[cn][sn].quizzes);
        }
          // freeing the students in the course
        free(st[cn]);
    }
      free(st);
}

// driver function
int main() 
{ 
  atexit(report_mem_leak); //for memory leak detector. 
  
  // double pointer for a 2D array for an array of arrays this will hold the courses(rows) and each       course has an array of students(columns)
  // this will hold whatever is returned from readCourses function which returns a 2D array (hence the   double pointer being used)
  student **courseList; 
  
  // variable declaration for counters 
  int i, j,C, N, M; 
  
  //passing reference of C, N, and M so that we get to know what we have in the first line 
  courseList = readCourses(&C, &N, &M); 
  printHighestTotal(courseList, C, N, M); 
  release_memory(courseList, C, N, M); 
  
  //free(ptr); 
  return 0; 
} 