TEST ONLY
===============


MySQL DECIMAL(string) to DOUBLE
----------
>
    $ sh build_mysql_test.sh && ./mysql_test
    MySQL Tables in mysql database:
    MySQL DECIMAL to DOUBLE test
    1 | 123456789012.12345678
    row[1]: 1, real (atof): 123456789012.123459
    real (stdtod): 123456789012.123459
    real (std::stod): 123456789012.123459
    real (std::stold): 123456789012.12345678
    real (std::stold): 123456789012.12345678
    -----
    2 | 999999999998.99999998
    row[1]: 2, real (atof): 999999999999.000000
    real (stdtod): 999999999999.000000
    real (std::stod): 999999999999.000000
    real (std::stold): 999999999999.00000000
    real (std::stold): 999999999999.00000000
    -----

