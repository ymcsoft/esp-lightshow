/**
 * Check if a specific bit is set in an integer
 * @param number: the integer to check
 * @param bit_position: position of bit to check (0 = least significant bit)
 * @return: true if bit is set, false otherwise
 */
bool isBitSet(int number, int bit_position) {
    return (number & (1 << bit_position)) != 0;
}