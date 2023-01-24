#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int const DEFAULT_ATTEMPS_OF_GAME = 10;

int char_length(char *string) 
    {
        int length = 0;
        while(string[length]) length++;
        return length;
    }

bool is_char_includes_in_string(char* string, char ch) 
    {
        int i = 0;
        while(i < char_length(string))
            {
                if(string[i] == ch) return false;
                else
                    {
                        i++;
                        continue;
                    }
                i++;
            }
        return true;
    }

int intialize_flag_t(int length_of_flags, char** flags)
    {
        int result = DEFAULT_ATTEMPS_OF_GAME;
        for(int i = 1; i < length_of_flags; i++)
            if(strcmp(flags[i] ,"-t") == 0) 
                {
                    i++;
                    result = atoi(flags[i]);
                }
        return result;
    }


char *get_random_number_codes()
    {
        int i = 0;
        char* result = (char*)malloc(5 * sizeof(char));
        srand(time(NULL));
        while(i  < 4)
            {
                char random_ascii_number =  rand() % 8 + '0';
                    if(is_char_includes_in_string(result, random_ascii_number)) 
                        {
                            result[i++] = random_ascii_number;
                        }   
            }
        result[i] = '\0';
        return result;
    }

char* intialize_flag_c(int argument_counter, char** argument_values)
    {
        char* result_code = NULL;
        for(int i = 1; i < argument_counter; i++)
            { 
                if(strcmp(argument_values[i] ,"-c") == 0)
                    {
                        i++;
                        result_code = argument_values[i];
                    }
                else
                    {
                        result_code = NULL;
                    }
            }
            if (result_code == NULL) 
                {
                    result_code = get_random_number_codes();
                }
        return result_code;   
    }

int get_miss_places_algo(char* guest_code, char* const_code)
    {
        int count = 0;
        int i = 0;
        while(i < char_length(guest_code))
            {
                if(!is_char_includes_in_string(guest_code, const_code[i]) && guest_code[i] != const_code[i])
                    {
                        count++; 
                    }
                i++;
            }
        return count;
    }

int get_well_pieces_algo(char* guest_code, char* const_code)
    {
        int my_result = 0;
        int i = 0;
        while (i < char_length(guest_code))
            {
                if (guest_code[i] == const_code[i])
                    {
                        my_result++;
                    }
                i++;
            }
        return my_result;
    }

int check_input_code(char* guest_inp_code)
    {
        for(int i = 0; i < char_length(guest_inp_code) - 1; i++)
            {
                for(int j = i+1; j < char_length(guest_inp_code); j++)
                    {
                        if (guest_inp_code[i] == guest_inp_code[j])
                            {
                                return 1;
                            }
                    }
            }
        return 0;
    }


bool under_ground(char* f_1, char f_2)
    {
        int v = 0; 
        while (v < char_length(f_1)){
            if (f_1[v] == f_2)
                return false;
            v++;
        }
        return true;
    }

char* get_input_cmd()
    {
        char *buffer_in = (char*)malloc(sizeof(char)* 255);
        int i = 0, return_read_inf = 0;
        char ch;
        while ((return_read_inf = read(0, &ch, 1)) > 0)
        { 
            if(ch != '\n')
                {
                    buffer_in[i] = ch;
                    i++;
                }
            else 
                {
                    return buffer_in;
                }
        }
        if(!return_read_inf)
            {
                exit(0);
            }
        return buffer_in;
    }

int check_buffer_for_valid(char* guest_inp_code)
    {
        if(char_length(guest_inp_code) != 4) 
            {
                return 1;
            }
        int i = 0;
        while (i < char_length(guest_inp_code)) 
            {
                if((guest_inp_code[i] > '7' && guest_inp_code[i] < '0') ) 
                    return 1;
                i++;
                }
        return 0;
    }

void print_round(int round_count)
    {
        printf("\n---\nRound %d\n", round_count); 
        write(1, ">", 1);
    }

void won_game()
    {
        printf("Congratulations! You can it!\n"); 
        printf("Congratz! You did it!"); 
        exit(0);
    }

void print_pieces(int w_count, int m_count)
    {
        printf("\nWell placed pieces: %d\n", w_count);
        printf("Misplaced pieces: %d", m_count);
    }


int main(int argument_counter, char** argument_values)
    {
        int attempts = 0;
        int well_places_pieces_count;
        int miss_places_pieces_count;
        int attempts_of_game = intialize_flag_t(argument_counter, argument_values);
        char* guest_code = intialize_flag_c(argument_counter, argument_values); 
        char *buffer_for_input = (char*)malloc(19*sizeof(char));
        printf("Will you find the secret code? \nPlease enter a valid guess");   
        while (attempts < attempts_of_game)
            {
                print_round(attempts);
                buffer_for_input = get_input_cmd();
                if (check_buffer_for_valid(buffer_for_input))
                    {
                        printf("\nYou did it wrong!"); 
                        continue;
                    }
                well_places_pieces_count = get_well_pieces_algo(guest_code, buffer_for_input);
                if (well_places_pieces_count == 4)
                    { 
                        won_game();
                    }
                miss_places_pieces_count = get_miss_places_algo(guest_code, buffer_for_input);
                print_pieces(well_places_pieces_count, miss_places_pieces_count); 
                attempts++;
            } 
        return 0; 
    }

