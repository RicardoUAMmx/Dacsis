
# Dacsis project

**Dacsis** is an implementation of a Data Engineering flow to process data
from a csv file. It is inspired by Pandas Data Frames, however it works in C.
For certain operations, and to have a reference, the dataset gonna be preprocesed
with bash tools.

The main objective of this project is to show how to implement a data engineering
in C and Bash with great performance, even faster than the popular ways to do it.

**Doesn't matter what programming language you use, the most important is to
understand the concepts and the data flow.**

## The dataset

The dataset used in this project is found in the `data` folder and is called
`openings.csv`. It contains information about chess openings.

BTW, the dataset has a header and we can count the number of columns based on
the number of commas (or separator in a file) in the first line.

```bash
head -n 1 data/openings.csv | tr ',' '\n' | wc -l
```

or

```bash
head -n 1 data/openings.csv | grep -o ',' | wc -l
```

Then we would use the second column to get each name in the dataset. However,
we must handle the case when the name its not in quotes. Thinking in bash we
could think in a quote as a separator. But:

```bash
head -n 210 data/openings.csv | cut -f2 -d'"' | tail
```

The output is:

```
Center Game, Berger Variation
Center Game, Normal Variation
Center Game, Paulsen Attack Variation
Clemenz Opening, General
['1.d4', 'd5', '2.Nf3', 'Nf6', '3.e3', 'e6']
['1.d4', 'd5', '2.Nf3', 'Nf6', '3.e3', 'e6', '4.Bd3']
Colle System, Traditional Colle
Czech Defense, General
Danish Gambit, Declined, Sorensen Defense
Danish Gambit, General
```

Theres much more in bash but we will use C to do the job.

```bash
./dacsis data/openings.csv | cut -f2 -d'"' | head -n 350 | tail
```

The output is:

```
Clemenz Opening	 General	
Colle System	
Colle System	
Colle System	 Traditional Colle	
Czech Defense	 General	
Danish Gambit	 Declined	 Sorensen Defense	
Danish Gambit	 General	
Dutch Defense	 Alekhine Variation	
Dutch Defense	 Blackburne Variation	
Dutch Defense	 Blackmar's Second Gambit	
```
