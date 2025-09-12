# Generating a board

The first step is to generate a solved board from which individual fields can be removed while making sure
to keep the number of possible solutions to one.

## Trivial things about solved boards

- A board needs to be `n×n` in size where `n` is a positive even integer number.
- Half of the fields are ones and the other half are zeros, their ratio is always 50:50

## Generating a solved board

### Small boards

#### 2×2

A `2×2` board is fairly straightforward: the board has `4` total fields, half of it are ones, the number of possible
valid boards are `4 [choose](https://en.wikipedia.org/wiki/Binomial_coefficient) 2` = `6`

```
00  01  11  10  10  01
11  01  00  10  01  10
```

> TODO: how many fields can be removed from a `2×2` board which would leave room for a single solution?

#### 4×4

The same formula doesn't work with `4x4`, because `16 choose 4` would also include having more than 2 of the same
fields next to each other, like the one below:

```
1111
1111
0000
0000
```

##### Generating a single row

Here we can simplify the question of how many valid boards there are by asking how many versions a single row
there are. When taking into accound that a row of 4 must contain 2 ones and 2 zeros then there are 6 possible
ways we can have those arranged:

```
// by rotating the row to the left (ROL)
0011
0110
1100
1001

// by inverting all the fields (INV)
0101
1010
```

##### Joining individual rows to form a board

> TODO: how to choose 4 of the 6 above possible rows to form a board? (with or without using repetition)

### Larger boards

Generating a board larger than `4×4` is not so trivial, so again let's first look at generating a single row.

#### All possible variations of a single row

There is a method which can generate all valid
rows adhearing to the rules of not having more than 2 of the same fields next to each other and having the
same amount of ones and zeros:

First start with an alternating block of `01` and fill the row with it. For a `6×6` board a single row would
look like this:

```
01 01 01
```

Each block can be normal or flipped and the previously created row is when all blocks are in normal state.

Write down all possible variations of these blocks: normal (`N`) and flipped (`F`)

```
N N N - 01 01 01
N N F - 01 01 10
N F N - 01 10 01
N F F - 01 10 10
F N N - 10 01 01
F N F - 10 01 10
F F N - 10 10 01
F F F - 10 10 10
```

Now rotate all of the above rows to the left or to the right once to get the other combinations:

```
N N N - 01 01 01 - 10 10 10
N N F - 01 01 10 - 10 11 00
N F N - 01 10 01 - 11 00 10
N F F - 01 10 10 - 11 01 00
F N N - 10 01 01 - 00 10 11
F N F - 10 01 10 - 00 11 01
F F N - 10 10 01 - 01 00 11
F F F - 10 10 10 - 01 01 01
```

Notice that the rotated `N N N` row is the same as the non-rotated `F F F` row, so from the rotated column
we can remove the first and the last rows, they are the only duplications:

```
N N N - 01 01 01
N N F - 01 01 10 - 10 11 00
N F N - 01 10 01 - 11 00 10
N F F - 01 10 10 - 11 01 00
F N N - 10 01 01 - 00 10 11
F N F - 10 01 10 - 00 11 01
F F N - 10 10 01 - 01 00 11
F F F - 10 10 10
```

Rewriting those rows under one another will make a list like so resulting in all the possible variations
of a single row:

```
010101
010110
011001
011010
100101
100110
101001
101010
101100
110010
110100
001011
001101
010011
```

This algorithm works for all larger rows, like a 8 field row of a `8×8` board. The total number of
possible rows can be calculated with the following formula:

```
# of possible rows = 2 * 2 ^ (n / 2) - 2
```

where `n` is the number of fields in a row:

| n   | # of possible rows   |
| --- | -------------------- |
| 4   | 6                    |
| 6   | 14                   |
| 8   | 30                   |
| 10  | 62                   |
| 12  | 126                  |
| n   | 2 \* 2 ^ (n / 2) - 2 |

The formula expects `n` to be divisible by 2, and larger or equal to 4.

#### Joining individual rows to form a board

> TODO: these are just random thoughts, these need to be cleaned up before implemented

##### Duplicating rows after each other

In a board a row can be duplicated only once right before or after the selected row
as having 2 of the same rows following one another doesn't violate the rules of binary sudoku.

Although before and after that the whole row needs to be inverted.

```
100101 <-- inverted row before
011010 <-- main row
011010 <-- duplicate
100101 <-- inverted row after
```

##### Possible ideas that might be useful

- pick a random row from all possible rows and place it randomly into the board
- keep a track of the number of ones and zeros used in each column
- if a column reaches `(n / 2)` in either zeros or ones then rows containing that specific value at the specific
  column can be removed and all subsequent rows need to be picked from the remaining rows

This seems to be a viable way of generating the last few rows of the table:
for an 8x8 table having 4 of the same values in a column can only occur after placing the 4th row if the rows
are placed randomly, or after placing the 6th row if rows are placed under one another.

> TODO: What are the limitations of placing the first 4 rows?

> TODO: how does placing the rows randomly differ from placing them in order?

---

## Combining rows into a board

An example will be shown using a 6x6 board.

Generating a board can be done row by row from going top to bottom.

Each subsequent row will take a look at previous rows above to find possible candidates that can fit in.
Rows with multiple options will act as points where generating can undo back if options run out before filling up the whole board.

### Step 0: generate all possible rows

Use the steps shown in the upper section of this document to generate all possible rows.

### Step 1: fill the first two rows with randomly picked rows

Nothing can go wrong by picking 2 rows, you are free to choose any rows (even use the same row twice) to fill out the 1st and 2nd rows.

For example the following 2 rows have been picked:

```
101100
011010
......
......
......
......
```

### Step 2: check above 2 rows for doubles and generate new row (with potential unknown values)

**Check using "Vertical neighbours check"**

Having two of the same values above in a column means the corresponding value below it needs to be the opposite.
Not all columns will have the same two values above it, in those cases the given cell has the option to hold both a 0 or a 1.

We can fill out the 3rd row with fixed values and `x` characters to mark unknown values:

```
101100
011010
xx0xx1
......
......
......
```

**Horizontally** there are no 2 or more fixed values clumped together, so no further checks are needed to be made here.

Otherwise the following checks would need to be made:

- having 2 of the same values next to each other preceeded by or followed by an `x` -> `x` can be turned into a fixed value
- having no matches for the pattern -> invalid row, undo back to previous multichoice row

**Vertically** there are no columns where an unknown cell is in a column with 3 or more ones, so no further eliminations are needed to be made there.

### Step 3: if new row has unknown values then find matches for it

`xx0xx1` will match for 3 rows:

```
010101
100101
010011
```

One of the rows need to be picked and we need to make sure to be able to return here and choose another row if all subsequent rows generate an invalid board.
Or if all rows fail, then go back even further to the row above that had multiple choices.

For the sake of examples let's go with picking the first row, so the board looks like this so far:

```
101100
011010
010101
......
......
......
```

### Repeat again from step 2 - selecting the 4th row:

Looking at rows 2 and 3 a pattern for row 4 can be created:

```
101100
011010
010101
10xxxx
......
......
```

2 values are next to each other, but they are not the same values, so no further horizontal checks are needed to be made here.

The sum of all ones per column is the following with the rows so far:

```
222211
```

None of them have reached or surpassed 3, so no further vertical checks are needed.

The pattern above will match 5 rows:

```
100101
100110
101001
101010
101100
```

Picking the 1st option again will result in a board that looks like so (including the sums below):

```
101100
011010
010101
100101
......
......
______
222312
```

### Row 5

Row 5 will have the following pattern:

```
101100
011010
010101
100101
xx1010
......
______
223322
```

`xx1010` matches 2 rows:

```
011010
101010
```

Picking the 1st match results in board like this:

```
101100
011010
010101
100101
011010
......
______
233322
```

### Row 6

The pattern of row 6 is the following:

```
101100
011010
010101
100101
011010
x000xx
______
233322
```

This doesn't match any of the possible rows, so we need to go back to the previous choice in row 5 and select a different row:

```
101100
011010
010101
100101
101010
......
______
323322
```

The pattern afterwards looks like this when looking at the above 2 rows:

```
101100
011010
010101
100101
101010
01xxxx
______
323322
```

Looking at the sums we can fill out fields with 0 where the column has maximum possible amount of ones:

```
101100
011010
010101
100101
101010
0100xx
______
323322
```

There's only one row that matches the pattern: `010011`

Inserting that will result in a fully generated board:

```
101100
011010
010101
100101
101010
010011
```
