#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;


//My code starts

void print_all_packages(town t) {
    printf("%s:\n",t.name);
    struct post_office* po = t.offices;
    for(int i=0; i<t.offices_count;i++, po++){
        printf("\t%d:\n",i);
        struct package* pk = (*po).packages;
        for(int j=0; j<(*po).packages_count;j++,pk++){
            printf("\t\t%s\n",(*pk).id);
        }
    }
}
//I tried writing this function but gave up
//Solution taken from <https://programs.programmingoneonone.com/2021/02/hackerrank-post-transition-solution-c.html>

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {	
    int n = 0;
    //Get count of number of packages to transfer
    for (int i = 0; i < source->offices[source_office_index].packages_count; i++)
        if (source->offices[source_office_index].packages[i].weight >= target->offices[target_office_index].min_weight &&
            source->offices[source_office_index].packages[i].weight <= target->offices[target_office_index].max_weight)
            ++n;
    
    //Allocate the new packages for source and target towns
    package* newPackages = malloc(sizeof(package)*(n + target->offices[target_office_index].packages_count));
    package* oldPackages = malloc(sizeof(package)*(source->offices[source_office_index].packages_count - n));

    for (int i = 0; i < target->offices[target_office_index].packages_count; i++) {
        newPackages[i] = target->offices[target_office_index].packages[i];
    }
    n = target->offices[target_office_index].packages_count;
    int m = 0;
    for (int i = 0; i < source->offices[source_office_index].packages_count; i++) {
        if (source->offices[source_office_index].packages[i].weight >= target->offices[target_office_index].min_weight &&
            source->offices[source_office_index].packages[i].weight <= target->offices[target_office_index].max_weight)
        {
            newPackages[n] = source->offices[source_office_index].packages[i];
            ++n;
        }
        else
        {
            oldPackages[m] = source->offices[source_office_index].packages[i];
            ++m;
        }
    }
    target->offices[target_office_index].packages_count = n;
    free(target->offices[target_office_index].packages);
    target->offices[target_office_index].packages = newPackages;
    source->offices[source_office_index].packages_count = m;
    free(source->offices[source_office_index].packages);
    source->offices[source_office_index].packages = oldPackages;
}

town town_with_most_packages(town* towns, int towns_count) {
    struct town* max_town = &towns[0];
    int max_count = -1;

    struct town* t = towns;
    for(int i=0;i<towns_count;i++,t++){
        int town_pkg_total = 0;
        struct post_office* po = (*t).offices;
        for(int j=0; j<(*t).offices_count;j++, po++){
            town_pkg_total += (*po).packages_count;
        }
        printf("%d",town_pkg_total);
        if(town_pkg_total > max_count){
            max_town = t;
            max_count = town_pkg_total;
        }
    }
    return *max_town;
}

town* find_town(town* towns, int towns_count, char* name) {
    struct town* t = towns;
    for(int i=0;i<towns_count;i++,t++){
        if(strcmp((*t).name,name)==0){
            break;
        }
    }
    return t;
}
//My code ends

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}