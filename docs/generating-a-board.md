# Generating a board

The first step is to generate a solved board from which individual fields can be removed while making sure
to keep the number of possible solutions to one.

## Trivial things about solved boards

- A board needs to be `n×n` in size where `n` is a positive even integer number.
- Half of the fields are ones and the other half are zeros, their ratio is always 50:50

## Generating all possible rows

```js
const n = 8;

function numberToBinaryString(i) {
  return i.toString(2).padStart(n, "0");
}

function countOnes(row) {
  const ones = row.split("").filter((number) => {
    return number === "1";
  });

  return ones.length;
}

function hasTooLargerGroup(row) {
  return /0{3,}|1{3,}/.test(row);
}

const rows = Array(1 << n)
  .fill(0)
  .map((_, i) => {
    // 2 ^ n
    return numberToBinaryString(i);
  })
  .filter((row) => {
    // n choose n / 2
    return countOnes(row) === n / 2;
  })
  .filter((row) => {
    // ?
    return !hasTooLargerGroup(row);
  });
```

---

| n   | 2 ^ n      | n choose (n / 2) | # of valid rows |
| --- | ---------- | ---------------- | --------------- |
| 2   | 4          | 2                | 2               |
| 4   | 16         | 6                | 6               |
| 6   | 64         | 20               | 14              |
| 8   | 256        | 70               | 34              |
| 10  | 1 024      | 252              | 84              |
| 12  | 4 096      | 924              | 208             |
| 14  | 16 384     | 3 432            | 518             |
| 16  | 65 536     | 12 870           | 1 296           |
| 18  | 262 144    | 48 620           | 3 254           |
| 20  | 1 048 576  | 184 756          | 8 196           |
| 22  | 4 194 304  | 705 432          | 20 700          |
| 24  | 16 777 216 | 2 704 156        | 52 404          |

\# of valid rows is on OEIS: https://oeis.org/A177790

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
