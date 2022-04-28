#include "wc.h"

extern struct team teams[NUM_TEAMS];
extern int test;
extern int finalTeam1;
extern int finalTeam2;

int processType = HOST;
const char *team_names[] = {
    "India", "Australia", "New Zealand", "Sri Lanka",   // Group A
    "Pakistan", "South Africa", "England", "Bangladesh" // Group B
};

void teamPlay(void)
{
  char *ip1 = malloc(1);
  char *ip2 = malloc(1);
  char *buff_mem = malloc(101);
  sprintf(buff_mem, "test/%d/inp/%s", test, teams[processType].name);
  read(teams[processType].commpipe[0], ip1, 1);
  int fpl = open(buff_mem, O_RDWR);

  while (1)
  {
    read(fpl, ip2, 1);
    write(teams[processType].matchpipe[1], ip2, 1);
    read(teams[processType].commpipe[0], ip1, 1);
    if (strcmp(ip1, "0") == 0)
      break;
  }
  close(fpl);
  free(buff_mem);
  exit(0);
}

void endTeam(int teamID)
{
  write(teams[teamID].commpipe[1], "0", 1);
}

int match(int team1, int team2)
{
  char a, b;
  char *buff_mem = (char *)malloc(101);
  write(teams[team1].commpipe[1], "1", 1);
  read(teams[team1].matchpipe[0], &a, 1);
  write(teams[team2].commpipe[1], "1", 1);
  read(teams[team2].matchpipe[0], &b, 1);

  int bat, ball;

  if ((a + b - 2 * '0') % 2 == 0)
    bat = team2;
  else
    bat = team1;

  if (bat == team1)
    ball = team2;
  else
    ball = team1;

  if ((team1 <= 3 && team2 > 3) == 1)
    sprintf(buff_mem, "test/%d/out/%sv%s-Final", test, teams[bat].name, teams[ball].name);
  else
    sprintf(buff_mem, "test/%d/out/%sv%s", test, teams[bat].name, teams[ball].name);

  int o_fpl = open(buff_mem, O_RDWR | O_CREAT, 0644);

  write(o_fpl, buff_mem, strlen(buff_mem));
  sprintf(buff_mem, "Innings1: %s bats\n", teams[bat].name);

  int t_score = 0, t2_runs = 0, batsman = 1, team1_score;

  for (int i = 0; i < 120; i++)
  {

    if (batsman == 11)
      break;
    write(teams[bat].commpipe[1], "1", sizeof(char));
    read(teams[bat].matchpipe[0], &a, sizeof(char));
    write(teams[ball].commpipe[1], "1", sizeof(char));
    read(teams[ball].matchpipe[0], &b, sizeof(char));
    if (a != b)
    {
      t_score += a - '0';
      t2_runs += a - '0';
    }
    else
    {
      sprintf(buff_mem, " %d :%d\n", batsman, t2_runs);
      write(o_fpl, buff_mem, strlen(buff_mem));
      t2_runs = 0;
      batsman++;
    }
  }
  if (batsman != 11)
  {
    sprintf(buff_mem, " %d\n :%d*\n", batsman, t2_runs);
    write(o_fpl, buff_mem, strlen(buff_mem));
  }

  team1_score = t_score;
  t_score = 0;
  t2_runs = 0;
  batsman = 1;
  sprintf(buff_mem, "%s TOTAL: %d\n", teams[bat].name, team1_score);
  write(o_fpl, buff_mem, strlen(buff_mem));

  int temp = bat;
  bat = ball;
  ball = temp;

  sprintf(buff_mem, "Innings2: %s bats\n", teams[bat].name);
  write(o_fpl, buff_mem, strlen(buff_mem));

  int winner = -1;
  for (int i = 0; i < 120; i++)
  {
    write(teams[bat].commpipe[1], "1", sizeof(char));
    write(teams[ball].commpipe[1], "1", sizeof(char));
    read(teams[bat].matchpipe[0], &a, sizeof(char));
    read(teams[ball].matchpipe[0], &b, sizeof(char));
    if (a == b)
    {
      sprintf(buff_mem, "%d:%d\n", batsman, t2_runs);
      batsman++;
      t2_runs = 0;
      write(o_fpl, buff_mem, strlen(buff_mem));
    }
    else
    {
      t2_runs += a - '0';
      t_score += a - '0';
    }
    if (t_score > team1_score)
    {
      winner = bat;
      break;
    }
    else if (batsman == 11)
    {
      if (t_score != team1_score)
        winner = ball;
      break;
    }
  }
  if (batsman != 11)
  {
    sprintf(buff_mem, "%d:%d*\n", batsman, t2_runs);
    write(o_fpl, buff_mem, strlen(buff_mem));
  }
  sprintf(buff_mem, "%s TOTAL: %d\n", teams[bat].name, t_score);
  write(o_fpl, buff_mem, strlen(buff_mem));
  if (winner == -1)
  {
    sprintf(buff_mem, "TIE: %s beats %s\n", teams[team1].name, teams[team2].name);
    winner = team1;
  }
  else if (winner == ball)
    sprintf(buff_mem, "%s beats %s by %d runs\n", teams[ball].name, teams[bat].name, team1_score - t_score);
  else
    sprintf(buff_mem, "%s beats %s by %d wickets\n", teams[bat].name, teams[ball].name, 11 - batsman);
  printf("%s\n", buff_mem);

  write(o_fpl, buff_mem, strlen(buff_mem));
  close(o_fpl);
  return winner;
}

void spawnTeams(void)
{
  pid_t pid = 1;
  char buff_mem[100];
  sprintf(buff_mem, "test/%d/out", test);
  mkdir(buff_mem, 0777);
  for (int i = 0; i < 8 && pid > 0; i++)
  {
    strcpy(teams[i].name, team_names[i]);
    pipe(teams[i].matchpipe);
    pipe(teams[i].commpipe);
    pid = fork();
    processType = i;
  }

  if (pid == 0)
  {
    teamPlay();
  }
}

void conductGroupMatches(void)
{
  int group_1[2];
  pipe(group_1);
  pid_t pid_a1 = fork();

  if (!pid_a1)
  {
    int Won_count[4], max_w = 0;
    for (int i = 0; i < 4; i++)
      Won_count[i] = 0;

    for (int i = 0; i <= 2; i++)
    {
      for (int j = i + 1; j < 4; j++)
      {
        int id_winner = match(i, j);
        Won_count[id_winner]++;
        max_w = max_w < Won_count[id_winner] ? Won_count[id_winner] : max_w;
      }
    }

    int flag = 0;
    for (int i = 0; i < 4; i++)
    {
      if (!flag && Won_count[i] == max_w)
      {
        write(group_1[1], &i, sizeof(int));
        flag = 1;
      }
      else
      {
        endTeam(i);
      }
    }
    exit(0);
  }

  int group_2[2];
  pipe(group_2);
  pid_t pid_a2 = fork();

  if (!pid_a2)
  {
    int Won_count[8], max_w = 0;
    for (int i = 0; i < 8; i++)
      Won_count[i] = 0;

    for (int i = 4; i <= 6; i++)
    {
      for (int j = i + 1; j < 8; j++)
      {
        int id_winner = match(i, j);
        Won_count[id_winner]++;
        max_w = max_w < Won_count[id_winner] ? Won_count[id_winner] : max_w;
      }
    }

    int flag = 0;
    for (int i = 4; i <= 7; i++)
    {
      if (!flag && Won_count[i] == max_w)
      {
        write(group_2[1], &i, sizeof(int));
        flag = 1;
      }
      else
      {
        endTeam(i);
      }
    }
    exit(0);
  }

  int flagg;
  waitpid(pid_a1, &flagg, 0);
  waitpid(pid_a2, &flagg, 0);
  read(group_1[0], &finalTeam1, sizeof(int));
  read(group_2[0], &finalTeam2, sizeof(int));
  printf("FT: %d FT:  %d\n", finalTeam1, finalTeam2);

  return;
}
