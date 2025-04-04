
# Import functions and testing modules for pytest.
from music_organization_system import calc_duration, \
    get_beat_note_number, get_time_signature, \
    get_tempo_category, make_title, make_dictionary, \
    get_random_bpm
import pytest

def test_calc_duration():
    '''Test the calc_duration function by calling
    it and comparing the returned values to the 
    expected values using assert.
    
    Parameters: None
    Return: None'''

    assert calc_duration(100, 83, 8) == ("6:38")
    assert calc_duration(30, 20, 4) == ("2:40")
    assert calc_duration(1000, 6000, 4) == ("24:00")
    assert calc_duration(80, 6027, 4) == ("301:21")

def test_get_beat_note_number():
    '''Test the get_beat_note function by calling
    it and comparing the returned values to the 
    expected values using assert.
    
    Parameters: None
    Return: None'''

    assert get_beat_note_number("") == (None)
    assert get_beat_note_number("half") == (2)
    assert get_beat_note_number("quarter") == (4)
    assert get_beat_note_number("eighth") == (8)

def test_get_time_signature():
    '''Test the get_time_signature function by calling
    it and comparing the returned values to the 
    expected values using assert.
    
    Parameters: None
    Return: None'''

    assert get_time_signature("", "") == ("/")
    assert get_time_signature("", 5) == ("/5")
    assert get_time_signature(6, "") == ("6/")
    assert get_time_signature(4, 4) == ("4/4")
    assert get_time_signature(6, 8) == ("6/8")
    assert get_time_signature(3, 4) == ("3/4")
    assert get_time_signature(2, 2) == ("2/2")

def test_get_tempo_category():
    '''Test the get_tempo_category function by calling
    it and comparing the returned values to the expected
    values using assert.
    
    Parameters: None
    Return: None'''

    assert get_tempo_category(-40) == ("Grave")
    assert get_tempo_category(0) == ("Grave")
    assert get_tempo_category(23) == ("Grave")
    assert get_tempo_category(41.3) == ("Lento")
    assert get_tempo_category(52) == ("Adagio")
    assert get_tempo_category(77) == ("Andante")
    assert get_tempo_category(90) == ("Moderato")
    assert get_tempo_category(100) == ("Allegretto")
    assert get_tempo_category(112) == ("Allegro")
    assert get_tempo_category(136.0) == ("Vivace")
    assert get_tempo_category(158) == ("Presto")
    assert get_tempo_category(178) == ("Prestissimo")
    assert get_tempo_category(1208759) == ("Prestissimo")

def test_make_title():
    '''Test the make_title function by calling it and 
    comparing its returned values to the expected values
    using various assert statements.
    
    Parameters: None
    Return: None'''

    assert make_title("jimmy") == ("Jimmy")
    assert make_title("") == ("")
    assert make_title("D") == ("D")
    assert make_title("hollywood studios") == ("Hollywood Studios")
    assert make_title("the best of both worlds") == ("The Best Of Both Worlds")
    assert make_title("tHe UGly dUCklIng") == ("The Ugly Duckling")
    assert make_title("how to find a penny") == ("How To Find A Penny")

def test_make_dictionary():
    '''Test the make_dictionary function by calling it and
    ensuring that it returns a dictionary type.
    
    Parameters: None
    
    Return: None'''

    # Define a test list of sample songs.
    songs = [['Go Wild', 'The Beatles', '6:27', 'Bach', 'English', '3/4', 'Grave'], 
    ['Mr Mom', 'Lonestar', '3:24', 'Countryclub', 'Spanish', '6/2', 'Adagio'], 
    ['Find Me Soon', 'Journey', '7:04', 'Bugtown Music', 'Irish', '9/8', 'Andante']]

    # Call the make_dictionary function using the test list of songs 
    # and store the result returned in a variable named song_dictionary.
    song_dictionary = make_dictionary(songs)

    # Confirm that the make_dictionary function returns a dictionary.
    assert isinstance(song_dictionary, dict), \
    "make_dictionary function must return a dictionary: " \
    f"a dictionary was expected but found a {type(song_dictionary)}"

def test_get_random_bpm():
    '''Tests the get_random_bpm function by calling it multiple times
    and checking to make sure the number it returns is an integer and 
    is within the correct range.
    
    Parameters: None
    
    Return: None'''

    # Call the get_random_bpm function a few times and store it as multiple variables.
    random_number_1 = get_random_bpm()
    random_number_2 = get_random_bpm()
    random_number_3 = get_random_bpm()
    random_number_4 = get_random_bpm()

    # Confirm that all the random-number variables are within the acceptable range
    # of the desired outcome.
    assert random_number_1 in range(1, 181)
    assert random_number_2 in range(1, 181)
    assert random_number_3 in range(1, 181)
    assert random_number_4 in range(1, 181)



# Call the main pytest function so that the computer will
# execute the test functions.
pytest.main(["-v", "--tb=line", "-rN", __file__])
