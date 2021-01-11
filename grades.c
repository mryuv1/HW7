

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked-list.h"



struct grades{
	struct list *mainList;
};

struct courses{
	char *course;
	int grade;
};

struct students{
	char *name;
	int id;
	struct list *courseList;
};


void element_destroy_course(void *element){
	struct courses* destroy = (struct courses*)element;
	free(destroy->course);
	free(destroy);
}

int clone_course(void *element, void **output){
	struct courses* new = (struct courses*)element;
	struct courses* copy = (struct courses*)malloc(sizeof(new));
	if (copy == NULL){
			return 1;
		}
	copy->course = (char*)malloc(sizeof(char)*(strlen(new->course)+1));
			if (copy->course == NULL){
					return 1;
			}
	strcpy(copy->course,new->course);
	//copy->course = new->course;
	copy->grade = new->grade;
	*output = (void*)copy;

		return 0;
}

int clone_students(void *element, void **output){
	struct students* new = (struct students*)element;
	struct students* copy = (struct students*)malloc(sizeof(new));
	if (copy == NULL){
		return 1;
	}
	copy->name = (char*)malloc(sizeof(char)*(strlen(new->name)+1));
		if (copy->name == NULL){
				return 1;
			}
	strcpy(copy->name,new->name);
	//copy->studuent = new->student;
	copy->id = new->id;
	copy->courseList = list_init(clone_course,element_destroy_course);
	*output = (void*)copy;
	return 0;
}


void destroy_students(void *element){
	struct students* destroy = (struct students*)element;
	list_destroy(destroy->courseList);
	free(destroy);
}




void grades_destroy(struct grades *grades){
	list_destroy(grades->mainList);
}


struct grades* grades_init(){
	struct grades tmp;
	struct grades *allStudents = malloc(sizeof(tmp));
	allStudents->mainList =list_init(clone_students, destroy_students);
	return  allStudents;
}

int grades_add_student(struct grades *grades, const char *name, int id){
	if (grades == NULL){
		return 1;
	}
	struct node *it = list_begin(grades->mainList);
	while (it){

			struct students *current = (struct students*)list_get(it);
			if (current->id == id){
				return 1;
			}
			it = list_next(it);
	}
	char tmp[sizeof(name)+1];
	strcpy(tmp,name);
	struct students newStudent;
	struct students *nnewStudent = &newStudent;
	newStudent.id = id;
	newStudent.name = (char*)tmp;

	//newStudent->name = name;


	if(!list_push_back(grades->mainList, nnewStudent)){
		return 0;
	}
	return 1;

}

int grades_add_grade(struct grades *grades, const char *name, int id, int grade){
	if ((grades == NULL) || (grade > 100)){
			printf("grades does not exist");
			return 1;
		}
	struct node *it = list_begin(grades->mainList);
	struct students *current = NULL;
		while (it){
				current = (struct students*)list_get(it);
				if (current->id == id){
					break;
				}
				it = list_next(it);
		}
		if (it == NULL){
			return 1;
		}

			struct node *that = list_begin(current->courseList);
			struct courses *ze = NULL;
		while (that){
				ze = (struct courses*)list_get(that);
				if (strcmp(ze->course,name) == 0){
					return 1;
				}
				that = list_next(that);


				}

	char tmp[sizeof(name)+1];
		strcpy(tmp,name);
		struct courses newGrade;
		struct courses *nnewGrade = &newGrade;
		newGrade.grade = grade;
		newGrade.course = (char*)tmp;
	if(!list_push_back(current->courseList, nnewGrade)){
			return 0;
		}
		return 1;

}

float grades_calc_avg(struct grades *grades, int id, char **out){

	if (grades == NULL){
				return -1;
			}
	struct node *it = list_begin(grades->mainList);
	struct students *current = NULL;
			while (it){
					current = (struct students*)list_get(it);
					if (current->id == id){
						break;
					}
					it = list_next(it);
			}
			if (it == NULL){

				return 1;
			}

	struct node *that = list_begin(current->courseList);
	char *ouaveraget = malloc(sizeof(char)*(strlen(current->name)+1));
		if (ouaveraget == NULL){
			printf("problem\n");
						return 1;
					}
		strcpy(ouaveraget, current->name);
		*out = ouaveraget;
	if (that == NULL){
		return 0;
	}
	int sum = 0;
	int counter = 0;
	while (that){
				struct courses *thatCourse = (struct courses*)list_get(that);
				sum += thatCourse->grade;
				counter += 1;
				that = list_next(that);
			}

	return ((float)sum/(float)counter);
}

int grades_print_student(struct grades *grades, int id){
	if (grades == NULL){
					return -1;
				}
	struct node *it = list_begin(grades->mainList);
	struct students *current = NULL;
			while (it){
					current = (struct students*)list_get(it);
					if (current->id == id){
						break;
					}
					it = list_next(it);
			}
			if (it == NULL){
				return 1;
			}

	printf("%s %d:" , current->name, current->id);

	struct node *that = list_begin(current->courseList);
	int counter = 1;
	while (that){
		struct courses *thiscourse = (struct courses*)list_get(that);
		printf(" COURSE-%d-%s COURSE-%d-%d," ,
				counter, thiscourse->course, counter, thiscourse->grade);
		counter += 1;
				}
	printf("\n");
	return 0;


}

int grades_print_all(struct grades *grades){
	if (grades == NULL){
					return -1;
				}
	struct node *it = list_begin(grades->mainList);

		int countStudents = 1;

		while (it){

			struct students *current = (struct students*)list_get(it);;
			printf("%s %d:" , current->name, current->id);

			struct node *that = list_begin(current->courseList);
			int counter = 1;
			while (that){
				struct courses *thiscourse = (struct courses*)list_get(that);
				if(list_next(that) != NULL){
					printf(" %s %d," ,thiscourse->course,thiscourse->grade);
					counter += 1;

				}else{
									printf(" %s %d" ,thiscourse->course,thiscourse->grade);
								}
					countStudents +=1;
					that = list_next(that);
			}
			printf("\n");
			it = list_next(it);
			}
	return 0;
}


