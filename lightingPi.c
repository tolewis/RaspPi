#include <stdio.h>
#include <wiringPi.h>

int lights[] = {0,1,2,7,6,5};

int main (int argc, char **argv)
{
  printf ("Raspberry Pi Automated Light Control\n") ;

  // Make sure we want to turn off a light
  if (argv[1] == NULL) {
    printf("You didn't type what light you want to toggle! Exiting!\n");
    exit(1);
  }

  // Let's set up wiringPi and some pins

  if (wiringPiSetup() == -1) return 1;

  int i = 0;
  // Set our light pins as output
  for (i = 0; i < sizeof(lights); i++) {
    pinMode(lights[i], OUTPUT);
  }

  // If we want to toggle
  if (strcmp(argv[1], "toggle") == 0) {

    if (argc < 4) {

      printf("Toggling light %s\n", argv[2]);

    } else { // Multiple lights
    
      // Loop through each argument after toggle
      for (int j = 0; j < argc - 2; j++) {         // Typecast our argument to an int         int light = (int)(argv[j + 2][0] - '0');         // Check to see if our light exists based on the size of the lights[] array
        if (light > (sizeof(lights) / 4)) {
          printf("Cannot toggle light %d as it does not exist.\n", light);
        } else {
          // Light exists so we can toggle it!
          printf("Toggling light %d\n", light);
          flipLight(lights[light - 1]);
        }
      }
    }

  } else if (strcmp(argv[1], "all") == 0) {
    printf("Toggling all lights!\n");
    int j = 0;
    for (j = 0; j < (sizeof(lights) / 4); j++) {
      flipLight(lights[j]);
    }
  } else {
    printf("Invalid argument! You must choose either \"toggle [pin]\" or \"all\"\n");

  }

  return 0;
}

void flipLight(int pin) {
  digitalWrite(pin, 1);
  delay(140);
  digitalWrite(pin, 0);
  delay(60);
}
