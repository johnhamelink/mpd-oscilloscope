#ifndef _OUTPUT_H
#define _OUTPUT_H
#include "output.h"
#endif

using namespace std;

/**
 * showError
 *
 * This function takes in a constant error,
 * adds a newline and prints it to STDERR, then
 * returns -1
 *
 * <code>
 *  return showError("Something went wrong");
 * </code>
 *
 * @param const char *err
 * @return int -1
 */
int showError(const char *err)
{
    cerr << string(err) + string("\n");
    return -1;
}

/**
 * showMsg
 *
 * This function takes in a constant message,
 * adds a newline and prints it to STDOUT, then
 * returns a 0
 *
 * @param const char *msg
 * @return int 0
 *
 */
int showMsg(const char *msg)
{
    cout << string("[Message]\t=> ") << string(msg) + string("\n");
    return 0;
}
