/*
	Kody Horstman
	EET 118 Final Project
	Class Management System
		This program allows a student to record and view information about previous semesters taken in 
		college classes as well as manage a profile.
*/

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>


/* Symbolic Constants */
// Profile
#define BUFF_STUDENT_ID 10
#define BUFF_STUDENT_FIRST 35
#define BUFF_STUDENT_LAST 35
#define BUFF_STUDENT_MAJOR 35
#define BUFF_STUDENT_GPA 5
// Class
#define MAX_CLASSES 7
#define BUFF_CLASS_SUBJECT 4
#define BUFF_CLASS_CODE 5
#define BUFF_CLASS_TITLE 35
#define BUFF_CLASS_CREDHOURS 3
#define BUFF_CLASS_PROF 70
#define BUFF_CLASS_LETGRADE 1
// Semester
#define MAX_SEMS 10
#define BUFF_SEMS_SCHOOL 71
#define BUFF_SEMS_SEASYEAR 12


/* Typedefs and Structures */
struct student {		// STUDENT structure
	char ID[BUFF_STUDENT_ID];
	char first[BUFF_STUDENT_FIRST];
	char last[BUFF_STUDENT_LAST];
	char major[BUFF_STUDENT_MAJOR];
	float GPA;
} profile;

typedef struct {		// Class structure
	char subject[BUFF_CLASS_SUBJECT];
	char code[BUFF_CLASS_CODE];
	char title[BUFF_CLASS_TITLE];
	char credHours[BUFF_CLASS_CREDHOURS];
	char prof[BUFF_CLASS_PROF];
	char letGrade;
} CLASS;

typedef struct {		// Semester structure
	char school[BUFF_SEMS_SCHOOL];
	unsigned int semCredHours;
	char SeasonYear[BUFF_SEMS_SEASYEAR];
	CLASS classes[MAX_CLASSES];
} SEMESTER;


/* Global Variables */
int nextSemIndex = 0;	// Holds the index for the next semeseter
unsigned char profileInited = '0';	// Boolean variable to hold whether the profile has been "initialized"
SEMESTER arrSemesters[MAX_SEMS];	// Array to hold semesters


/* Prototypes */
int main(void);				// Program flow
void clrscr(void);			// Clears console
void viewSemester(void);	// Show semester info
void addSemester(void);		// Add a new semester
void viewProfile(void);		// Show profile info
void updateProfile(void);	// Change profile info


/* Program flow. Prints main menu, determines choice, and calls the according function */
int main(void) {
	
	// Variable
	unsigned int choice;

	
	// Infinite loop
	while (1) {
		// Prompt User for choice
		// Main menu
		puts("\n\n\tSelect an option.");
		puts("\t1  View Semester");
		puts("\t2  Add Semester");
		puts("\t3  View Profile");
		puts("\t4  Update Profile");
		puts("\t5  Exit\n");
		printf("\t>> ");
		scanf("%d", &choice);
		fflush(stdin);
		
		
		// Verify choice
		switch (choice) {
			case 1:
				// Option 1: View Semester
				clrscr();
				viewSemester();
				break;
			case 2:
				// Option 2: Add Semester
				clrscr();
				addSemester();
				break;
			case 3:
				// Option 3: View Profile
				clrscr();
				viewProfile();
				break;
			case 4:
				// Option 4: Update Profile
				clrscr();
				updateProfile();
				break;
			case 5:
				// Option 5: Exit
				puts("\n\tPress ENTER to continue...");
				getch();
				return 0;
			default:
				// Error Message: Invalid Option
				fprintf(stderr, "\tERROR: Invalid Option.\n");
				continue;
		} // end switch
	} // end while
	return 0;
} // end main


/* Clears console */
void clrscr(void) {
	system("cls");
}


/* Show semester info */
void viewSemester(void) {
	char seasonYear[BUFF_SEMS_SEASYEAR];	// Holds the semester name to be searched
	int i, j;	// Counters
	// Test that there are semesters in array
	if (nextSemIndex > 0) {
		// Get the semester to be searched
		do {
			printf("\n\tEnter the semester you wish to view:");
			for (i = 0; i < nextSemIndex; i++) {
				printf("\n\t\t%s", arrSemesters[i].SeasonYear);
			}
			printf("\t>> ");
			// prompt for semester to be searched
			fgets(seasonYear, BUFF_SEMS_SEASYEAR, stdin);
		} while (seasonYear[0] == '\n');
	} else {
		// Inform the student there are no semesters added and exit function
		printf("\n\tNo Semesters to view.");
		return;
	}
	
	// Begin looping through the semesters
	for (i = 0; i <= nextSemIndex; i++) {
		// Find the semester the student asked for
		if (strcmp(seasonYear, arrSemesters[i].SeasonYear) == 0) {
			printf("\n\tSchool: %s", arrSemesters[i].school);
			printf("\tSemester Credit Hours: %d", arrSemesters[i].semCredHours);
			printf("\n\tSemester: %s", arrSemesters[i].SeasonYear);
			
			puts("\n\t--------------------------------------------------------------------------------------------------------------");
			puts("\tClasses:");
			printf("\t%-4s\t%-4s\t%-35s\t%-35s\t%-5s\t%-5s", "Subj", "Code", "Title", "Prof", "Creds", "Grade");
			for (j = 0; j < MAX_CLASSES; j++) {
				// That the subject of the class is not null
				if (arrSemesters[i].classes[j].subject == "\0") {
					// If it is null, exit the class loop
					break;
				} else {
					// If it is not null, print the information
					printf("\n\t%-4s\t%-4s\t%-35s\t%-35s\t%-5s\t%c", 
							arrSemesters[i].classes[j].subject, 
							arrSemesters[i].classes[j].code, 
							arrSemesters[i].classes[j].title, 
							arrSemesters[i].classes[j].prof,
							arrSemesters[i].classes[j].credHours,
							arrSemesters[i].classes[j].letGrade);
				}
			}
			break; // exit the loop
		} else {
			// If the current one is not the one the student asked for, go to the next iteration of the loop
			continue;
		}
		// if no semester is found, inform the student
		printf("\n\tNo such semester.");
	}
}


/* Add a new semester */
void addSemester(void) {
	int j, k, numClasses;
		
	if (nextSemIndex <= MAX_SEMS) {
		printf("\n\tSemester %d", nextSemIndex + 1);
		
		printf("\n\tSchool name: ");
		fgets(arrSemesters[nextSemIndex].school, BUFF_SEMS_SCHOOL, stdin);
		fflush(stdin);
		if (arrSemesters[nextSemIndex].school[BUFF_SEMS_SCHOOL - 1] == '\n') {
			arrSemesters[nextSemIndex].school[BUFF_SEMS_SCHOOL - 1] == '\0';
		}
		
		printf("\tTotal credit hours: ");
		scanf("%d", &arrSemesters[nextSemIndex].semCredHours);
		fflush(stdin);
		
		printf("\tSeason and year: (summer 1969) ");
		fgets(arrSemesters[nextSemIndex].SeasonYear, BUFF_SEMS_SEASYEAR, stdin);
		fflush(stdin);
		for (k = 0; k < BUFF_SEMS_SEASYEAR; k++) {
			if (arrSemesters[nextSemIndex].SeasonYear[k] == '\n'){
				arrSemesters[nextSemIndex].SeasonYear[k] == '\0';
			}
		}
		
		do {
			printf("\tHow many classes did you take this semester? (7 or less) ");
			scanf("%d", &numClasses);
			fflush(stdin);
		} while (numClasses > MAX_CLASSES || numClasses < 0);
		
		for (j = 0; j < numClasses; j++) {
			puts("\t--------------------------------------------------------");
			printf("\tClass %d:", j + 1);
			
			// Subject
			printf("\n\tSubject: (Ex. EET) ");
			fgets(arrSemesters[nextSemIndex].classes[j].subject, BUFF_CLASS_SUBJECT, stdin);
			fflush(stdin);
			for (k = 0; k < BUFF_CLASS_SUBJECT; k++) {
				if (arrSemesters[nextSemIndex].classes[j].subject[k] == '\n') {
					arrSemesters[nextSemIndex].classes[j].subject[k] = '\0';
					break;
				}
			}
			// Code
			printf("\tCourse code: (Ex. 101) ");
			fgets(arrSemesters[nextSemIndex].classes[j].code, BUFF_CLASS_CODE, stdin);
			fflush(stdin);
			fflush(stdin);
			for (k = 0; k < BUFF_CLASS_CODE; k++) {
				if (arrSemesters[nextSemIndex].classes[j].code[k] == '\n') {
					arrSemesters[nextSemIndex].classes[j].code[k] = '\0';
					break;
				}
			}
			// Title
			printf("\tTitle: (Ex. Circuit Analysis I) ");
			fgets(arrSemesters[nextSemIndex].classes[j].title, BUFF_CLASS_TITLE, stdin);
			fflush(stdin);
			for (k = 0; k < BUFF_CLASS_TITLE; k++) {
				if (arrSemesters[nextSemIndex].classes[j].title[k] == '\n') {
					arrSemesters[nextSemIndex].classes[j].title[k] = '\0';
					break;
				}
			}
			// Credit Hours
			printf("\tCourse credit hours: (Ex. 4) ");
			fgets(arrSemesters[nextSemIndex].classes[j].credHours, BUFF_CLASS_CREDHOURS, stdin);
			fflush(stdin);
			for (k = 0; k < BUFF_CLASS_CREDHOURS; k++) {
				if (arrSemesters[nextSemIndex].classes[j].credHours[k] == '\n') {
					arrSemesters[nextSemIndex].classes[j].credHours[k] = '\0';
					break;
				}
			}
			// Prof
			printf("\tWhat was the professor's name: (Ex. William Kelsey) ");
			fgets(arrSemesters[nextSemIndex].classes[j].prof, BUFF_CLASS_PROF, stdin);
			fflush(stdin);
			for (k = 0; k < BUFF_CLASS_PROF; k++) {
				if (arrSemesters[nextSemIndex].classes[j].prof[k] == '\n') {
					arrSemesters[nextSemIndex].classes[j].prof[k] = '\0';
					break;
				}
			}
			// Grade
			printf("\tGrade: (Ex. B) ");
			scanf("%c", &arrSemesters[nextSemIndex].classes[j].letGrade);
			fflush(stdin);
		}
		nextSemIndex++;
		clrscr();
	} else {
		printf("\n\tYou've already reached maximum semesters.");
	}
}


/* Show profile info */
void viewProfile(void) {
	// Test that profile has been initialized
	if (profileInited == '1') {	
		// Print profile
		printf("\n\tProfile Information:");
		printf("\n\tID:\t%s", profile.ID);
		printf("\n\tNAME:\t%s, %s", profile.last, profile.first);
		printf("\n\tMAJOR:\t%s", profile.major);
		printf("\n\tGPA:\t%.2f", profile.GPA);
		puts("");
	} else {
		// Initialize profile
		updateProfile();
	}
}


/* Change profile info */
void updateProfile(void) {
	// Update profileInited
	if (profileInited == '0') {
		profileInited = '1';
	}
	
	
	char *testBuff = (char *)malloc(35 * sizeof(char));	// To hold input for testing
	float testGPA;	// To hold GPA input for testing
	
	// Allow the user to change profile data
	printf("\n\tProfile Update:\n");
	
	// ID
	printf("\tID:\t(%s) ", profile.ID);
	gets(testBuff);
	if (strcmp(testBuff, "")) {
		fflush(stdin);
		strcpy(profile.ID, testBuff);
		strcpy(testBuff, "");
	}
	
	// First
	printf("\tFIRST:\t(%s) ", profile.first);
	gets(testBuff);
	if (strcmp(testBuff, "")) {
		fflush(stdin);
		strcpy(profile.first, testBuff);
		strcpy(testBuff, "");
	}
	
	// Last
	printf("\tLAST:\t(%s) ", profile.last);
	gets(testBuff);
	if (strcmp(testBuff, "")) {
		fflush(stdin);
		strcpy(profile.last, testBuff);
		strcpy(testBuff, "");
	}
	
	// Major
	printf("\tMajor:\t(%s) ", profile.major);
	gets(testBuff);
	if (strcmp(testBuff, "")) {
		fflush(stdin);
		strcpy(profile.major, testBuff);
		strcpy(testBuff, "");
	}
	
	// GPA
	printf("\tGPA:\t(%.2f) ", profile.GPA);
	gets(testBuff);
	if (testGPA = atof(testBuff)) {
		profile.GPA = testGPA;
		testGPA = 0.0;
	}
	
	// Display changes
	viewProfile();
	
	return;
}


