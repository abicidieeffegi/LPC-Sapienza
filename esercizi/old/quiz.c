#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct domande{
  char domanda[256];
  int risposta;
};

int main() {
  struct domande culturagenerale[] = {
    { "The star sign Aquarius is represented by a tiger", 0 },
    { "A is the most common letter used in the English language", 0 },
    { "ASOS stands for As Seen On Screen", 1 },
    { "The battle of Hastings took place in 1066", 1 },
    { "H&M stands for Hennes & Mauritz", 1 },
    { "K is worth four points in Scrabble", 1 },
    { "In a deck of cards, the king has a moustache", 0},
    { "The sum of the numbers on opposite sides in a dice is always 7", 1 },
    { "In the English language there is no word that rhymes with orange", 1 },
    { "English is the most spoken language in the world", 0 }
  };
  struct domande animali[] = {
    { "The unicorn is the national animal of Scotland", 1 },
    { "A cross between a horse and a zebra is called a Hobra", 0 },
    { "A lion's roar can be heard up to eight kilometres away", 1 },
    { "Canis lupur is the scientific name for a wolf", 0 },
    { "An octopus has three hearts", 1 },
    { "Fish cannot blink", 1 },
    { "Goldfish have a two second memory", 0 },
    { "In Finding Nemo the protagonist is a pufferfish", 0 },
    { "Hippos sweat a red substance", 1 },
    { "The first animal sent into space was a monkey", 0 },
  };
  struct domande film[] = {
    { "Meryl Streep has won two Academy Awards", 0 },
    { "Idina Menzel sings 'let it go' 20 times in 'Let It Go' from Frozen", 0 },
    { "In Harry Potter, Draco Malfoy has no siblings", 1 },
    { "Cinderella was the first Disney princess", 0 },
    { "Walt Disney holds the record for the most Oscars", 1 },
    { "Emma Roberts is the daughter of Julia Roberts", 0 },
    { "Timothée Chalamet went to the same school as Nicki Minaj", 1 },
    { "Emily Blunt and Stanley Tucci are related", 1 },
    { "Titanic was released in 1999", 0 },
    { "Avatar is the highest grossing movie of all time", 1 }
  };
  struct domande scienza[] = {
    { "The atomic number for lithium is 17", 0 },
    { "The black box in a plane is black", 0 },
    { "There are two parts of the body that can't heal themselves", 0 },
    { "There are five different blood groups", 0 },
    { "Alexander Fleming discovered penicillin", 1 },
    { "Your 'radius' bone is in your leg", 0 },
    { "The only letter not in the periodic table is the letter J", 1 },
    { "The small intestine is about three-and-a-half times the length of your body", 1 },
    { "Thomas Edison discovered gravity", 0 },
    { "Venus is the hottest planet in the solar system", 1 }
  };

  printf("QUIZ GAME:\n");
  printf("\t1. General knowledge\n\t2. Animals\n\t3. Movies\n\t4. Science\n");
  printf("Choose your topic (1-4): ");
  int scelta, k, score = 0;
  unsigned int seed = time(0);
  scanf("%d", &scelta);

  // controllo
  while (scelta < 1 || scelta > 4) {
    printf("Error. Unrecognised choice.\nEnter your choice (1-4)");
    scanf("%d", &scelta);
  }

  // cultura generale
  if (scelta == 1) {
    // trovo il numero di elementi dell'array
    size_t max = sizeof(culturagenerale)/sizeof(culturagenerale[0]);
    for (int i=1; i<=5; i++) {
      // pesco e stampo una domanda random nell'array 
      int k = rand_r(&seed) % max;
      printf("%d. %s\n", i, culturagenerale[k].domanda);
      // prendo l'input dell'utente per verificare se la risposta è giusta;
      printf("True or false? (T - F)\n");
      int r_user;
      scanf(" %c", &r_user);
      while (r_user != 'T' && r_user != 't' && r_user != 'F' && r_user != 'f') {
        printf("Unrecognised answer. True or false? ");
        scanf("%c", &r_user);
      }
      int r_int;
      if (r_user == 'T' || r_user == 't')
        r_int = 1;
      else 
        r_int = 0;
      if (r_int == culturagenerale[k].risposta) {
        printf("Great! Correct answer!\n");
        score++;
        printf("Your score is now %d\n", score);
      }
      else {
        printf("Wrong answer\n");
        score--;
        printf("Your score is now %d\n", score);
      }
    }
  }
  // animali
  else if (scelta == 2) {
    // trovo il numero di elementi dell'array
    size_t max = sizeof(animali)/sizeof(animali[0]);
    for (int i=1; i<=5; i++) {
      // pesco e stampo una domanda random nell'array 
      int k = rand_r(&seed) % max;
      printf("%d. %s\n", i, animali[k].domanda);
      // prendo l'input dell'utente per verificare se la risposta è giusta;
      printf("True or false? (T - F)\n");
      int r_user;
      scanf(" %c", &r_user);
      while (r_user != 'T' && r_user != 't' && r_user != 'F' && r_user != 'f') {
        printf("Unrecognised answer. True or false? ");
        scanf("%c", &r_user);
      }
      int r_int;
      if (r_user == 'T' || r_user == 't')
        r_int = 1;
      else 
        r_int = 0;
      if (r_int == animali[k].risposta) {
        printf("Great! Correct answer!\n");
        score++;
        printf("Your score is now %d\n", score);
      }
      else {
        printf("Wrong answer\n");
        score--;
        printf("Your score is now %d\n", score);
      }
    }
  }
  // film
  else if (scelta == 3) {
    // trovo il numero di elementi dell'array
    size_t max = sizeof(film)/sizeof(film[0]);
    for (int i=1; i<=5; i++) {
      // pesco e stampo una domanda random nell'array 
      int k = rand_r(&seed) % max;
      printf("%d. %s\n", i, film[k].domanda);
      // prendo l'input dell'utente per verificare se la risposta è giusta;
      printf("True or false? (T - F)\n");
      int r_user;
      scanf(" %c", &r_user);
      while (r_user != 'T' && r_user != 't' && r_user != 'F' && r_user != 'f') {
        printf("Unrecognised answer. True or false? ");
        scanf("%c", &r_user);
      }
      int r_int;
      if (r_user == 'T' || r_user == 't')
        r_int = 1;
      else 
        r_int = 0;
      if (r_int == film[k].risposta) {
        printf("Great! Correct answer!\n");
        score++;
        printf("Your score is now %d\n", score);
      }
      else {
        printf("Wrong answer\n");
        score--;
        printf("Your score is now %d\n", score);
      }
    }
  }
  // scienza
  else if (scelta == 4) {
    // trovo il numero di elementi dell'array
    size_t max = sizeof(scienza)/sizeof(scienza[0]);
    for (int i=1; i<=5; i++) {
      // pesco e stampo una domanda random nell'array 
      int k = rand_r(&seed) % max;
      printf("%d. %s\n", i, scienza[k].domanda);
      // prendo l'input dell'utente per verificare se la risposta è giusta;
      printf("True or false? (T - F)\n");
      int r_user;
      scanf(" %c", &r_user);
      while (r_user != 'T' && r_user != 't' && r_user != 'F' && r_user != 'f') {
        printf("Unrecognised answer. True or false? ");
        scanf("%c", &r_user);
      }
      int r_int;
      if (r_user == 'T' || r_user == 't')
        r_int = 1;
      else 
        r_int = 0;
      if (r_int == scienza[k].risposta) {
        printf("Great! Correct answer!\n");
        score++;
        printf("Your score is now %d\n", score);
      }
      else {
        printf("Wrong answer\n");
        score--;
        printf("Your score is now %d\n", score);
      }
    }
  }
  return 0;
}
