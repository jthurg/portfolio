
"""This program will help musicians to enter information
about the music they are writing into a program. The 
program will make calculations regarding the song 
duration and the tempo category for each song. It 
will also allow the user to input the information 
about the author, composer, language, and other 
related information for each song. It will take
all of the information and make an album/playlist 
for the user, which will actually be a dictionary. 
This will make it very convenient for a musician 
to organize and store the information about their 
music into a digital library."""

# Import necessary modules.
import random

# Define the main function.
def main():
    
    # Define empty list of songs.
    songs = []

    # Define a blank dictionary to be the song playlist.
    playlist_dict = {}

    # Define a variable to contain the menu text so it can easily
    # be printed multiple times.
    menu_text = ('''
    Main Menu
              
    Please enter the number of the task you wish to execute:
    1. Add Song
    2. Remove Song
    3. Display Entered Songs
    4. Create and Write Album/Playlist
    5. Quit''')

    # Define menu-selection boolean to start the main menu loop.
    menu_done = False
    
    # Loop through the 5 menu options.
    while not menu_done:
        
        # Start the loop by displaying the menu text.
        print(menu_text)
        print()
        print("What would you like to do?")

        # Ask the user to select a number option from the menu.
        menu_selection = int(input('Enter a number from the menu: '))

        ### Menu Option 1: Add Song ###
        if menu_selection == 1:

            # Define booleans for bpm, measures, beats_per_measure, and
            # the beat_note_name so that loops can be used to ensure 
            # the user enters a valid entry.
            have_bpm = False
            have_measures = False
            have_beats_per_measure = False
            have_beat_note_name = False

            # Define a blank list for all the song information.
            song_info = []

            # Define a song_exists and have_name boolean for the loop to check if
            # song is already in the list of songs and whether or not the name was 
            # recorded.
            song_exists = None
            have_name = False

            # Check if song is already in the song list using a loop.
            # We can't have duplicates since we will be making it a dictionary.
            while not have_name:

                # Get the song name and format it as a title.
                song_name = input("Please enter the name/title of the song: ")
                song_name = make_title(song_name)

                # Iterate through each song name to see if the name that the user just 
                # entered is already in use.
                for song in songs:
                    if song_name in song:
                        song_exists = True
                    else:
                        song_exists = False

                # If the song name is already in use, display an error message
                # and restart the loop.
                if song_exists == True:
                    print("That song is already entered.")
                    print("Please enter a different song name.")
                    have_name = False
                
                # If the name is not in use, then exit the loop.
                else: 
                    have_name = True
            
            # Add song_name to the song_info list.
            song_info.append(song_name)

            # Get the artist name and format it as a title.
            artist = input("Please enter the name of the artist/band: ")
            artist = make_title(artist)

            # Add artist to the song_info list.
            song_info.append(artist)

            # Start a loop to ensure bpm entered is greater than 0.
            while not have_bpm:

                # Ask user if they want to enter a bpm or choose a random one.
                print()
                print("Select one of the options regarding the bpm (beats per minute): ")
                print("1. I want to enter a bpm")
                print("2. I want a random bpm")
                print()
                random_bpm = int(input("Please enter the number you wish to select: "))

                # Check if they chose option 1.
                if random_bpm == 1:

                    # If so, have them enter their bpm.
                    bpm = int(input("Please enter the bpm (beats per minute): "))

                    # Check to make sure the bpm is greater than 0.
                    if bpm <= 0:
                        print("BPM must be greater than 0.")
                        print("Please try again.")

                    # If it is greater than 0, then exit the loop.
                    else:
                        have_bpm = True

                # Check if they chose option 2.
                elif random_bpm == 2:

                    # If so, call the get_random_bpm function and save it as the bpm.
                    bpm = get_random_bpm()
                    have_bpm = True
                
                # If the user entered an invalid number, show an error message
                # and restart the loop.
                else:
                    print("That is not a valid entry please try again.")

            # Start a loop to make sure the user enters a valid number for the 
            # measures variable.
            while not have_measures:

                # Ask for the number of measures.
                measures = int(input('Please enter the number of measures: '))

                # If the number of measures is less than or equal to 0, then
                # display an error message and let the loop restart.
                if measures <= 0:
                    print("Measures must be greater than 0.")
                    print("Please try again.")
                
                # If the number of measures is greater than 0, 
                # then exit the loop.
                else:
                    have_measures = True

            # Start a loop to make sure the user enters a valid number
            # for the beats_per_measure.
            while not have_beats_per_measure:

                # Ask the user for the beats_per_measure.
                beats_per_measure = int(input("Please enter the number of beats per measure (2, 3, 4, 6, 9, 12): "))

                # Define a list of acceptable entries for the beats_per_measure.
                beats_list = [2, 3, 4, 6, 9, 12]

                # If the beats_per_measure is not in the list of acceptable entries, 
                # then display an error message and restart the loop.
                if beats_per_measure not in beats_list:
                    print("That is not a valid entry for beats per measure.")
                    print("Please try again.")

                # If the beats_per_measure is in the list of acceptable entries, 
                # then exit the loop.
                else:
                    have_beats_per_measure = True
            
            # Call the calc_duration function to determine the song length.
            song_length = calc_duration(bpm, measures, beats_per_measure)

            # Add song_length to the song_info list.
            song_info.append(song_length)

            # Get the composer name and format it as a title.
            composer = input("Please enter the name of the composer: ")
            composer = make_title(composer)

            # Add composer to the song_info list.
            song_info.append(composer)

            # Get the song language and format it as a title.
            language = input('Please enter the language of the song: ')
            language = make_title(language)

            # Add the language to the song_info list.
            song_info.append(language)

            # Start a loop to ensure the user enters a valid beat_note_name.
            while not have_beat_note_name:

                # Ask user to enter a beat_note_name.
                beat_note_name = input("What note gets one beat? (half, quarter, eighth): ")

                # Check to see if the beat_note_name matches the valid options, and if so end the loop.
                if beat_note_name.lower() == "half" or \
                    beat_note_name.lower()== "quarter" or \
                    beat_note_name.lower()== "eighth":
                    beat_note_num = get_beat_note_number(beat_note_name)
                    have_beat_note_name = True
                
                # If the beat_note_name doesn't match the valid entries, then
                # display an error message and restart the loop.
                else:
                    print("That does not match one of the options.")
                    print("Please try again.")
            
            # Call get_time_signature function to determine the time signature.
            time_signature = get_time_signature(beats_per_measure, beat_note_num)

            # Add time_signature to the song_info list.
            song_info.append(time_signature)

            # Call the get_tempo_category function to determine the tempo name.
            tempo_name = get_tempo_category(bpm)

            # Add tempo_name to the song_info list.
            song_info.append(tempo_name)

            # Add all the song info to the list of songs.
            songs.append(song_info)

        ### Menu Option 2: Remove Song ###
        elif menu_selection == 2:

            # Define the song number counting variable at 0
            # so that we can use it to count the songs displayed.
            song_number = 0

            # Iterate through each song.
            for song in songs:

                # Add 1 to the count.
                song_number += 1

                # Display the song and its number.
                print(f"{song_number}. {song}")
            print()

            # Ask user which song they wish to remove.
            remove_song_num = int(input("Enter the number of the song you wish to remove: "))

            # Remove the song that corresponds to the number the user entered.
            remove_index = remove_song_num - 1
            songs.pop(remove_index)
            
        ### Menu Option 3: Display Songs ###
        elif menu_selection == 3:

            # Start a count at 0.
            count = 0

            # Display the intro statement before the songs loop.
            print()
            print("Songs:")

            # Iterate through the songs.
            for song in songs:

                # Add 1 to the count.
                count += 1

                # Display the song and its number.
                print(f"{count}. {song}")

        ### Menu Option 4: Create and Write Album/Playlist ###
        elif menu_selection == 4:

            # Define booleans to allow us to creates a loop that will 
            # ensure the user has the option of going back instead of
            # fully committing to ending the program by making the playlist.
            make_playlist = None
            playlist_loop = True

            # Display the prompt about making the playlist that will end the program.
            print()
            print("If you choose to write the playlist, you will not be")
            print("able to go back and add any more songs and the program will end.")

            # Start the playlist loop.
            while playlist_loop:

                # Ask if the user wishes to make the playlist and end the program.
                make_playlist = input("Do you wish to write the playlist and end now? (yes/no) ")

                # Check if the user entered 'yes'.
                if make_playlist.lower() == "yes":
                    
                    # Call the make_dictionary function to create the music playlist.
                    print()
                    playlist_dict = make_dictionary(songs)

                    # Display the end message for the program.
                    print("Thank you for using our program!")
                    print("Here is the playlist you generated:")
                    print()

                    # Display the playlist of songs.
                    for key, value in playlist_dict.items():
                        print(f"{key}: {value}")
                    print()

                    # End the menu-selection and playlist loop.
                    menu_done = True
                    playlist_loop = False

                # Check if the user enetered 'no'.
                elif make_playlist.lower() == "no":

                    # End the playlist loop.
                    playlist_loop = False

                # If the user entered anything besides 'yes' or 'no',
                # then display an error message.
                else:
                    print("That is not a validy entry.")

        ### Menu Option 5: Quit ###
        elif menu_selection == 5:

            # If the user chose option 5, quit the menu loop.
            menu_done = True

        ### Menu Option Error ###
        else:
            print()
            print(f"Error: {menu_selection} is not a valid entry.")
            print("Please try again.")
            print()

    # Display Program Finish Message.
    print()
    print("Thank you for using this program.")
    print("Enjoy your music!")
    print()

def calc_duration(bpm, num_measures, beats_per_measure):
    '''Calculates the duration of a song using
    the bpm (beats per minute), the number 
    of measures, and the beats per measure. Returns the duration of the song
    in timer format as a string (ex. 4 minutes and
    23 seconds would return 4:23).
    
    Parameters
        bpm: beats per minute entered by the user
        num_measures: the number of measures for
            the entire song (each contains 4 beats)
        beats_per_measure: how many beats there are in each measure
    Return song duration in timer format as a string.'''

    # Calculate total beats.
    total_beats = (num_measures * beats_per_measure)

    # Determine number of whole minutes and seconds.
    minutes = total_beats / bpm
    whole_minutes = int(minutes // 1)
    seconds_decimal = round(minutes - whole_minutes, 2)
    whole_seconds = int(60 * seconds_decimal)

    # Create string from minutes and seconds.
    min_string = str(whole_minutes)
    if whole_seconds <= 9:
        sec_string = "0" + str(whole_seconds)
    else:
        sec_string = str(whole_seconds)

    # Combine min and sec strings and save as duration.
    # Then return the duration.
    duration = min_string + ":" + sec_string
    return duration

def get_time_signature(beats_per_measure, beat_note_number):
    '''Determines the time signature of the song using the beats_per_measure 
    and the beat_note_number. Returns the time signature as a
    string in time-signature format. (ex: If beats_per_measure = 4 and 
    beat_note_number = 8 then the function would return "4/8" where the top number 
    is beats_per_measure and bottom number is the beat_note_number)
    
    Parameters
        beats_per_measure: the number of beats per measure of the song
        beat_note_number: the number that corresponds to the note that gets 1 beat'''
    
    # Convert beats_per_measure and beat_note_number to strings and then combine in 
    # time signature format (ex: "4/8") and save as time_signature.
    time_signature = str(beats_per_measure) + "/" + str(beat_note_number)

    # Return the time signature.
    return time_signature

def get_beat_note_number(beat_note_name):
    '''Determines and returns the corresponding number for a specific
    beat note. This number corresponds to the specific name of the beat
    note entered (ex: "quarter" would return 4, "half" would return 2, and
    "eighth" would return 8).
    
    Parameters
        beat_note_name: the name of the type of note that gets 1 beat in the song
    
    Return beat note number'''
    
    # Check if the beat_note_name is "half", "quarter", or "eighth"
    # and then define beat_note_number to the corresponding number value.
    if beat_note_name.lower() == "half":
            beat_note_number = 2
    elif beat_note_name.lower() == "quarter":
            beat_note_number = 4
    elif beat_note_name.lower() == "eighth":
            beat_note_number = 8
    else:
        beat_note_number = None

    # Return the beat_note_number.
    return beat_note_number

def get_tempo_category(bpm):
    '''Determines and returns the name of the tempo 
    category based on the bpm of the song as a string.
    
    Parameters
        bpm: beats per minute of the song
        
    Return the name of the tempo category'''
    
    # Check the bpm number and classify it with
    # the corresponding tempo name.
    if bpm <= 40:
        tempo = "Grave"
    elif bpm > 40 and bpm <= 50:
        tempo = "Lento"
    elif bpm > 50 and bpm <= 60:
        tempo = "Adagio"
    elif bpm > 60 and bpm <= 80:
        tempo = "Andante"
    elif bpm > 80 and bpm <= 90:
        tempo = "Moderato"
    elif bpm > 90 and bpm <= 104:
        tempo = "Allegretto"
    elif bpm > 104 and bpm <= 132:
        tempo = "Allegro"
    elif bpm > 132 and bpm <= 140:
        tempo = "Vivace"
    elif bpm > 140 and bpm <= 177:
        tempo = "Presto"
    elif bpm > 177:
        tempo = "Prestissimo"

    # Return the tempo name.
    return tempo

def make_title(string):
    '''Formats a string into gramatic title-format.
    
    Parameters
        string: any string (in this case it will be a name/title)
        
    Return the title-formatted string'''

    # Use the title method on the string.
    title_str = string.title()

    # Return the title_formatted string.
    return title_str

def make_dictionary(song_info_list):
    '''Creates and returns a dictionary from a list 
    of the song information for the songs the user has
    stored in the songs list. It returns the dictionary
    with the song name as the key and all of the other
    related information as the value.
    
    Parameters
        song_info_list: a list with all of the information about
            the different songs the user has stored up in the program
            
    Return a dictionary of the songs stored in the program'''

    # Define an empty list for the keys and values of the dictionary.
    keys = []
    values = []

    # Define needed indexes.
    SONG_TITLE_INDEX = 0

    # Iterate through each song, defining the keys and values.
    for song in song_info_list:
        key = song[SONG_TITLE_INDEX]
        keys.append(key)
        song.pop(SONG_TITLE_INDEX)
        value = song
        values.append(value)

    # Create the song-dictionary using the list of keys as keys
    # and the list of values as values respectively.
    song_dict = dict((key, value) for key, value in zip(keys, values))

    # Return the created song-dictionary.
    return song_dict

def get_random_bpm():
    '''Generates and returns a random integer from 1 to 180 and 
    then stores it to a bpm variable. Returns the bpm.
    
    Parameters: None
    
    Return bpm (random integer from 1 to 180)'''

    # Generate a random integer for the bpm that is greater than 0 
    # and less than 181.
    bpm = random.randint(1, 180)

    # Return the random integer that was saved as the bpm.
    return bpm

# Execute the main program while making sure the test program can still run too.
if __name__ == "__main__":
    main()
