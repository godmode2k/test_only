// MySQL Decimal(string) to double test
// - hjkim, 2019.04.16



// MySQL: decimal table
// CREATE TABLE IF NOT EXISTS test_decimal (
// idx INT(20) UNSIGNED NOT NULL AUTO_INCREMENT,
// value DECIMAL(20, 8) NOT NULL,
// PRIMARY KEY (idx) );
//
// INSERT INTO test_decimal VALUES ( 0, 123456789012.12345678 );
// INSERT INTO test_decimal VALUES ( 0, 999999999998.99999998 );
//
//
// Dependencies:
// $ sudo apt-get install libmysql++-dev
//
//
// Build:
// $/usr/bin/g++ -o mysql_test mysql_test.cpp -Wall -O2 -std=c++11 -I/usr/include/mysql -I/usr/include/mysql++ -lmysqlpp -lmysqlclient
// or
// $ sh build_mysql_test.sh
//
//
// Result:
// MySQL Tables in mysql database:
// MySQL DECIMAL to DOUBLE test
// 1 | 123456789012.12345678
// row[1]: 1, real (atof): 123456789012.123459
// real (stdtod): 123456789012.123459
// real (std::stod): 123456789012.123459
// real (std::stold): 123456789012.12345678
// real (std::stold): 123456789012.12345678
// -----
// 2 | 999999999998.99999998
// row[1]: 2, real (atof): 999999999999.000000
// real (stdtod): 999999999999.000000
// real (std::stod): 999999999999.000000
// real (std::stold): 999999999999.00000000
// real (std::stold): 999999999999.00000000
// -----


// Source-based: (MySQL client example)
// https://stackoverflow.com/questions/8896963/connecting-to-mysql-through-c



#include <iostream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <mysql.h>
#include <mysql++.h>


// just going to input the general details and not the port numbers
struct connection_details {
	char *server;
	char *user;
	char *password;
	char *database;
};

MYSQL* mysql_connection_setup(struct connection_details mysql_details) {
	// first of all create a mysql instance and initialize the variables within
    MYSQL *connection = mysql_init(NULL);

	// connect to the database with the details attached.
    if (!mysql_real_connect(connection,
				mysql_details.server,
				mysql_details.user,
				mysql_details.password,
				mysql_details.database,
				0, NULL, 0)) {
		printf("Conection error : %s\n", mysql_error(connection));
		exit(1);
	}
	return connection;
}

MYSQL_RES* mysql_perform_query(MYSQL *connection, char *sql_query) {
	// send the query to the database
	if (mysql_query(connection, sql_query)) {
		printf("MySQL query error : %s\n", mysql_error(connection));
		exit(1);
	}

	return mysql_use_result(connection);
}

int main(void) {
	MYSQL *conn;      // the connection
	MYSQL_RES *res;   // the results
	MYSQL_ROW row;    // the results row (line by line)
	
	struct connection_details mysqlD;
	mysqlD.server = "localhost";  // where the mysql database is
	mysqlD.user = "";     // the root user of mysql   
	mysqlD.password = ""; // the password of the root user in mysql
	mysqlD.database = "";    // the databse to pick

	// connect to the mysql database
	conn = mysql_connection_setup(mysqlD);

	// assign the results return to the MYSQL_RES pointer
	//res = mysql_perform_query(conn, "show tables");
	res = mysql_perform_query(conn, "select * from test_decimal");


	printf("MySQL Tables in mysql database:\n");



	printf( "MySQL DECIMAL to DOUBLE test\n" );
	while ((row = mysql_fetch_row(res)) != NULL) {
		printf( "%s | %s\n", row[0], row[1] );
		printf( "row[1]: %s, real (atof): %f\n", row[0], atof(row[1]) );
		printf( "real (stdtod): %f\n", strtod(row[1], NULL) );

		printf( "real (std::stod): %f\n", std::stod(row[1]) );
		printf( "real (std::stold): %.8Lf\n", std::stold(row[1]) );

		long double val = std::stold(row[1]);
		printf( "real (std::stold): %.8Lf\n", val );

		// https://en.cppreference.com/w/cpp/io/manip/setprecision
		//std::cout << "std::setprecision(10): " << std::setprecision(10) << val << "\n"
		//	<< "max precision:         "
		//	<< std::setprecision(std::numeric_limits<long double>::digits10 + 1)
		//	<< val;

		printf( "-----\n" );
	}



	// clean up the database result set 
	mysql_free_result(res);

	// clean up the database link 
	mysql_close(conn);

	return 0;
}
