# CS302/proj2
Gauge Zidlick https://github.com/gzidlick/CS302/edit/master/proj2/

1.

| Mode    | Size     | Elapsed Time  |
|---------|-------   |---------------|
| STL     | 10       | 0.002         | 
| STL     | 100      | 0.002         | 
| STL     | 1000     | 0.007         | 
| STL     | 10000    | 0.019         | 
| STL     | 100000   | 0.192         |
| STL     | 1000000  | 2.239         | 
| STL     | 10000000 | 25.221        |
| QSORT   | 10       | 0.003         | 
| QSORT   | 100      | 0.002         | 
| QSORT   | 1000     | 0.004         | 
| QSORT   | 10000    | 0.017         | 
| QSORT   | 100000   | 0.173         |
| QSORT   | 1000000  | 1.947         | 
| QSORT   | 10000000 | 9.42          |
| MERGE   | 10       | 0.003         | 
| MERGE   | 100      | 0.002         | 
| MERGE   | 1000     | 0.004         | 
| MERGE   | 10000    | 0.364         | 
| MERGE   | 100000   | 2.293         | 
| MERGE   | 1000000  | 0.672         | 
| MERGE   | 10000000 | 6.332         | 
| QUICK   | 10       | 0.003         | 
| QUICK   | 100      | 0.004         | 
| QUICK   | 1000     | 0.004         | 
| QUICK   | 10000    | 0.02          | 
| QUICK   | 100000   | 0.168         | 
| QUICK   | 1000000  | 1.95          | 
| QUICK   | 10000000 | 9.33          | 

2a. The elasped times of the sorting algorithms remains pretty close up until about 100K elements. From there, you can see that STL sort starts to take longer, growing sharply at 10mil elements. The reason for this large increase is because STL sort uses a version of merge sort, as the lists get larger the amount of elements in a partition goes up as well as the amount of partitions. QSORT and QUICKSORT grew at about the same rate, at 10mil elements QUICKSORT was just slightly faster. I am unsure of these numbers however because for both QSORT and QUICK only at 10mil elements did they seg fault. I had the same issue with mergesort where large input sizes were causing seg faults.



2b.These show that theoretical complexies are exactly that, theoretical. Real-world variances such as hardware can effect execution times as well as things like pivot choice and number of elements.



2c. Out of the choices, I would choose quick sort because it works well with small lists and the average time scales well as lists get bigger and bigger.


3. I worked solo on this project. I understand that in my quick sort implementation I was not supposed to use arrays to implement the sort, I wanted to demonstrate that I understood how the algorithm worked in order to try and get partial credit. I had a hard time managing pointers in my utility functions, my main issue was that pointers kept getting lost and I did not know the reason. I had the same issues with merge sort, so for that reason I also used arrays to implement the algorithm. As for the seg faults at larger numbers, I speculate that such large input sizes are not suited for arrays and it is causing it to go out of bounds. I also realize that there are memory issues with my program, I tried using valgrind to trace the cause but could not find an answer.
