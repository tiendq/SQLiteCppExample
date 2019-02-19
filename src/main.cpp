#include <exception>
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;

int main() {
  // Using SQLITE_VERSION would require #include <sqlite3.h> which we want to avoid.
  // Use SQLite::VERSION if possible.
  cout << "SQLite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")" << '\n';
  cout << "SQLiteC++ version " << SQLITECPP_VERSION << '\n';

  try {
    // Open a database file in create/write mode
    SQLite::Database db("test.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    cout << "SQLite database file " << db.getFilename() << " opened successfully\n";

    // Create a new table with an explicit "id" column aliasing the underlying rowid
    db.exec("DROP TABLE IF EXISTS test");
    db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");

    string sql = "INSERT INTO test VALUES (NULL, 'first')";

    int nb = db.exec(sql);
    cout << sql << " returned " << nb << '\n';

    sql = "INSERT INTO test VALUES (NULL, 'second')";
    nb = db.exec(sql);
    cout << sql << " returned " << nb << '\n';

    sql = "UPDATE test SET value='second-updated' WHERE id=2";
    nb = db.exec(sql);
    cout << sql << " returned " << nb << '\n';

    string count = db.execAndGet("SELECT COUNT(*) FROM test");
    cout << "COUNT(*) = " << count << '\n';

    // Check the results, expect two rows
    sql = "SELECT * FROM test";
    SQLite::Statement query(db, sql);
    cout << sql << '\n';

    while (query.executeStep())
      cout << "row (" << query.getColumn(0) << ", " << query.getColumn(1) << ")\n";

    SQLite::Statement countQuery(db, "SELECT COUNT(*) FROM test WHERE id=:id");
    countQuery.bind(":id", 2);

    while (countQuery.executeStep())
      cout << "COUNT(*) with conditionals " << countQuery.getColumn(0) << '\n';

    db.exec("DROP TABLE test");
  } catch (exception const &e) {
    cout << "SQLite exception: " << e.what() << '\n';
    return EXIT_FAILURE;
  }

  remove("test.db3");

  return EXIT_SUCCESS;
}
