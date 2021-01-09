

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked-list.h"



struct grades{
	const char *student;
	int id;
	struct list *course;
};

struct courses{
	const char *course;
	int grade;
};



void element_destroy_course(void *element){
	struct courses* destroy = (struct courses*)element;
	free(destroy);
}

int clone_course(void *element, void **output){
	struct courses* new = (struct courses*)element;
	struct courses* copy = (struct courses*)malloc(sizeof(new));
	if (copy == NULL){
			return 1;
		}
	copy->course = new->course;
	copy->grade = new->grade;
	output = (void **)copy;

		return 0;
}

int clone_grades(void *element, void **output){
	struct grades* new = (struct grades*)element;
	struct grades* copy = (struct grades*)malloc(sizeof(new));
	if (copy == NULL){
		return 1;
	}
	copy->student = new->student;
	copy->id = new->id;
	copy->course = list_init(clone_course,element_destroy_course);
	output = (void **)copy;
	return 0;
}


void destroy_grades(void *element){
	struct grades* destroy = (struct grades*)element;
	list_destroy(destroy->course);
	free(destroy);
}


void grades_destroy(struct grades *grades){
	list_destroy((struct list*)grades);
}

struct grades* grades_init(){
	struct grades *students =(struct grades*)list_init(clone_grades, destroy_grades);
	printf("ttt\n");
	return  students;
}

int grades_add_student(struct grades *grades, const char *name, int id){
	printf("bbb\n");
	if (grades == NULL){
		printf("grades does not exist");
		return 1;
	}
	struct node *it = list_begin((struct list*)grades);
	printf("ccc\n");
	while (it){
		printf("ddd\n");
			struct grades *current = (struct grades*)list_get(it);
			if (current->id == id){
				printf("student alredy exist");
				return 1;
			}
			it = list_next(it);
	}
	printf("eee\n");
	struct grades *newStudent;

	newStudent->id = id;

	newStudent->student = *name;
	printf("fff\n");

	if(!list_push_back((struct list*)grades, newStudent)){
		return 0;
	}
	return 1;

}

int grades_add_grade(struct grades *grades, const char *name, int id, int grade){
	if (grades == NULL){
			printf("grades does not exist");
			return 1;
		}
	struct node *it = list_begin((struct list*)grades);

		while (it){
				struct grades *current = (struct grades*)list_get(it);
				if (current->id == id){
					break;
				}
				it = list_next(it);
		}
		if (it == NULL){
			printf("student doesn't exists");
			return 1;
		}
	struct list *tmp = ((struct grades*)list_get(it))->course;
	struct courses *newGrade;
	newGrade->course = name;
	newGrade->grade = grade;

	if(!list_push_back(tmp, newGrade)){
			return 0;
		}
		return 1;

}

float grades_calc_avg(struct grades *grades, int id, char **out){

	if (grades == NULL){
				printf("grades does not exist");
				return -1;
			}
	struct node *it = list_begin((struct list*)grades);

	while (it){
			struct grades *current = (struct grades*)list_get(it);
			if (current->id == id){
			break;
			}
			it = list_next(it);
		}
	if (it == NULL){
			printf("student doesn't exists");
			return -1;
	}
	struct node *that = list_begin(((struct grades*)list_get(it))->course);
	if (that == NULL){
		return 0;
	}
	int sum = 0;
	int counter = 0;
	while (that){
				struct courses *current = (struct courses*)list_get(it);
				sum += current->grade;
				counter += 1;
			}

	*out = malloc(sizeof(char)*(strlen(((struct grades*)list_get(it))->student)+1));
	strcpy(*out, ((struct grades*)list_get(it))->student);

	return (float)sum/(float)counter;
}

int grades_print_student(struct grades *grades, int id){
	if (grades == NULL){
					printf("grades does not exist");
					return -1;
				}
	struct node *it = list_begin((struct list*)grades);

		while (it){
					struct grades *current = (struct grades*)list_get(it);
						if (current->id == id){
							break;
						}
					it = list_next(it);
			}

		if (it == NULL){
				printf("student doesn't exists");
				return -1;
		}

	printf("STUDENT-%s STUDENT-%d:" , ((struct grades*)list_get(it))->student, ((struct grades*)list_get(it))->id);

	struct node *that = list_begin((struct list*)(((struct grades*)list_get(it))->course));
	int counter = 1;
	while (that){
		struct courses *current = (struct courses*)list_get(that);
		printf(" COURSE-%d-%s COURSE-%d-%d," ,
				counter, current->course, counter, current->grade);
		counter += 1;
				}
	printf("\n");
	return 0;


}

int grades_print_all(struct grades *grades){
	if (grades == NULL){
					printf("grades does not exist");
					return -1;
				}
		struct node *it = list_begin((struct list*)grades);

		int countStudents = 1;

		while (it){

			struct grades *current = (struct grades*)list_get(it);
			printf("STUDENT-%d-%s STUDENT-%d-%d:" , countStudents, current->student, countStudents, current->id);

			struct node *that = list_begin(((struct grades*)list_get(it))->course);
			int counter = 1;
			while (that){
				struct courses *current = (struct courses*)list_get(it);
				printf(" COURSE-%d-%s COURSE-%d-%d," ,
						counter, current->course, counter,current->grade);
						counter += 1;
								}
					printf("\n");
					countStudents +=1;

			}
	return 0;
}


