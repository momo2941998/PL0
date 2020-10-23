#include <stdio.h>
#include "scanner.h"
#include <ctype.h>
#include <string.h>

TokenType Token;
int Num; // từ vụng nhận được khi token là NUMMBER
char Id[MAX_IDENT_LEN + 1]; // từ vựng nhận được khi token là IDENT

FILE *f;
char ch;

TokenType checkKeyword(char *str)
{
  //TODO: kiểm tra xâu str có phải từ khóa không
  char tmp[100];
  strcpy(tmp, str);
  for (int i = 0; i < strlen(tmp); i++)
    tmp[i] = toupper(tmp[i]);
  for (int i = 0; i < KEYWORDS_COUNT; i++)
  {
    if (!strcmp(keywords[i].string, tmp))
    { // strcmp return 0 if two string equal
      return keywords[i].Token;
    }
  }
  return NONE;
}

void readNext()
{
  ch = getCh();
  // printf("\n read: %d",(unsigned int) ch);
}

char getCh()
{
  return fgetc(f);
}

TokenType getToken()
{
  //TODO: đọc đầu vào, trả về token

  //Ch chua ky tu doc duoc tu van ban nguon boi ham getCh()
  while (ch == ' ' || ch == '\n' || ch == '\t')
    readNext();

  if (isalpha(ch))
  { // IDENT
    int length = 0;
    Id[length] = ch;
    readNext();
    while (isalpha(ch) || isdigit(ch)){
      length++;
			if(length > MAX_IDENT_LEN) {
				readNext();
			} else {
				Id[length] = ch;
				readNext();
			}
    }
    if (length > MAX_IDENT_LEN) {
      length++;
      Id[MAX_IDENT_LEN] = '\0';
    }
    else {
      length++;
      Id[length] = '\0';
    }
    return IDENT;
  }

  if (isdigit(ch))
  { // NUMBER
    int length = 1;
    Num = ch - '0';
    readNext();
    while (isdigit(ch)){
      int tmp = Num * 10 + (ch - '0');
      if (1) {
        length++;
        Num = tmp;
      }
      if (length > MAX_NUMBER_LEN) return NONE;
      readNext();
    }
    return NUMBER;
  }

  if (ch == '+')
  { // PLUS
    readNext();
    return PLUS;
  }

  if (ch == '-')
  { // MINUS
    readNext();
    return MINUS;
  }

  if (ch == '*')
  { // TIMES
    readNext();
    return TIMES;
  }

  if (ch == '/')
  { // SLASH
    readNext();
    return SLASH;
  }

  if (ch == '=')
  { // EQU
    readNext();
    return EQU;
  }

  if (ch == '<')
  {
    readNext();
    if (ch == '>')
    { //NEQ: <>
      readNext();
      return NEQ;
    }
    else if (ch == '=')
    { // LEQ: <=
      readNext();
      return LEQ;
    }
    else return LSS;
  }

  if (ch == '>')
  {
    readNext();
     if (ch == '=')
    { // GEQ: >=
      readNext();
      return GEQ;
    }
    else return GTR; // >
  }

  if (ch == '(')
  { // LPARENT
    readNext();
    return LPARENT;
  }

  if (ch == ')')
  { // RPARENT
    readNext();
    return RPARENT;
  }

  if (ch == '[')
  { // LBRACK
    readNext();
    return LBRACK;
  }

  if (ch == ']')
  { // RBRACK
    readNext();
    return RBRACK;
  }

  if (ch == ':')
  { // MINUS
    readNext();
    if (ch == '=')
    { // ASSIGN
      readNext();
      return ASSIGN;
    }
    return NONE; // error
  }

  if (ch == ';')
  { // SEMICOLON
    readNext();
    return SEMICOLON;
  }

  if (ch == ',')
  { // COMMA
    readNext();
    return COMMA;
  }

  if (ch == '.')
  { // PERIOD
    readNext();
    return PERIOD;
  }

  if (ch == '%')
  { // PERCENT
    readNext();
    return PERCENT;
  }

  return NONE;
}

void compile(char *filename)
{
  f = fopen(filename, "rt");
  if (f == NULL)
    printf("File %s not found", filename);
  else
  {
    ch = ' ';
    do
    {
      Token = getToken();
      printf(" %s", TabToken[Token]);
      if (Token == IDENT)
        printf("(%s) \n", Id);
      else if (Token == NUMBER)
        printf("(%d) \n", Num);
      else
        printf("\n");
    } while (Token != NONE);
    fclose(f);
  }
}

// int main(int argc, char const *argv[])
// {
//   char str[10] = "program";
//   int x = checkKeyword(str);
//   printf("%s (%s)", str,TabToken[x]);
//   return 0;
// }
