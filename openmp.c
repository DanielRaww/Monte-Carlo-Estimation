// Daniel Raw, Gabriel Espinoza
// CSCI312

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
//void *compute_pi (void *);

// Each thread uses a random function to generate its own number of samples (sample_points_per_thread in slide 9). Control the random number generator to produce reasonable number of samples with high accuracy and reasonable execution time for computing Pi.
// Use an OpenMP reduction in the end to sum up all the samples from different threads and compute Pi.
// If your code does not give an accurate Pi or runs for long time, we will deduct points.
// pi = 3.1415./9265359...

int hits[4] = {0,0,0,0};
//int threads_num = 4;
int compute_pi(int a){

    double x_cord, y_cord; //initialize the x_cord and y _cord
    int local_hits = 0; //sets local hits to 0
//    int i = 9500000 +rand()%1000; //amount of times iterated
    int c, i;
    i = (rand() % (999999 - 99999 + 1) + 99999);
    //srand(100000);
    /*for (c=1; c <= 10; c++) {
      i = rand() % 999999 + 100000;
    }*/

    int j; //initalize j variable
    for (j = 0; j < i; j++ ){ //for loop that runs i many iterations
        x_cord = (double)rand() / (RAND_MAX)-0.5; //monte carlo formula, get cordinates between [-0.5, 0.5]
        y_cord = (double)rand() / (RAND_MAX)-0.5;
        if (x_cord * x_cord + y_cord * y_cord <= 0.25){  //test to see if point is inside circle
            local_hits += 1; //increment local hits
        }

}
    hits[a] = i; //sets hits[a] to i
    return local_hits;
}

int main(){//int argc, const char **argv){

 /* const char * read_var = getenv("OMP_NUM_THREADS");
  int threads_num = atoi(read_var);

    double pi; //create a double variable called pi
    int sum = 0, add = 0; //initialize sum and add
     int i = atoi (argv[1]);  //integer representation of argc[1] is stored in i

    if (argc != 2) {
      printf("You need pass at least two parameters");
      exit(-1);
    }
    else {
      const int threads_num = atoi(argv[1]);
    }
*/
    double pi; //create a double variable called pi
    int sum = 0, add = 0; //initialize sum and add

#pragma omp parallel reduction(+:sum, add) num_threads(threads_num)
//create a team of threads, we are reducing all scalar variables in sum and add with +.4 is passed in num_threads.
    {
#pragma omp sections //several section constructs
        {
#pragma omp section //execute section construct first
            {
                sum = compute_pi(0); //have sum equal to compute_pi with 0 being passed
                add = hits[0]; //have add equal to hits[0]
            }
#pragma omp section
            {
                sum = compute_pi(1); //have sum equal to compute_pi with 1 being passed
                add = hits[1]; //have add equal to hits[1]
            }
#pragma omp section
            {
                sum = compute_pi(2); //have sum equal to compute_pi with 2 being passed
                add = hits[2]; //have add equal to hits[2]
            }
#pragma omp section
            {
                sum = compute_pi(3); //have sum equal to compute_pi with 3 being passed
                add = hits[3]; //have add equal to hits[3]
            }
        }
#pragma omp barrier //won't run past this parallel region


    }


    pi = (double)sum/add*4;
 //   printf("run %d times\n", add);
    printf("pi is equal to %f.\n", pi);


}
