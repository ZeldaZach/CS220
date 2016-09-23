Zachary Halpern
9/16/16

Question #1:
I first check if the number is the end cases or out of bounds. If so, return the appropriate value. Next, I turn the long into an array with each char labeled by itself. Ex: 123 becomes arr{1, 2, 3}. Now, I determine if the number is below 1000. If so, I only have to run it through the count hundreds function. 

The count_hundreds function checks the first number (the hundreds place) and turns it to words then adds the word "hundred". Now, with the last two digits it will check if it starts with a 1. If so, then it calls for the edge "teen" cases and adds them. If it's not a 1, then it will use the tens value ("twenty", "thirty" etc) for the number then check the single digit for the value.

The count_thousands function calls the count_hundreds function on the first 3 numbers of the set (Ex: 123456 gives 123) and then appends "thousand". The if statement then calls the count_hundreds function on the last 3 numbers.

The count_millions function calls the count_hundreds function on the first 3 numbers of the set (Ex: 123456789 gives 123) and then appends "thousand". The if statement then calls the count_thousands on the next 3 numbers (456) and then the if statement calls the count_hundreds function on the last 3 numbers.

Question #2:
I create an array of length 32 and set all values to 0. Now, I run through the input integer and turn it into a binary sequence, putting it into this array (Ex: 5 = 00000000000000000000000000000101). If the number is negative, then I flip the number (Ex: -5 => 5) and set a flip flag for later. Now, if I don't have to flip the number, I go through and use a for loop to count up the 1's and return this value. If I have to flip it, then I start by flipping all the values through a foor loop, then use another loop to see if, when adding, I need to carry a bit over to the next row. If I do, then the loop continues. If not, then the loop exits and we go to counting the 1's.

Question #3:
I start by creating an array of 4 char's in length, which is long enough to contain the 4 bytes of the integer. To set it, I use a bitwise right accounting for the 8 bits of the integer times however far along it is. Now, I use a temp variable to swap everything around and return the array converte back into an integer.