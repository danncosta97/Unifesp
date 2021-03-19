<?php
  $host="webdev.zapto.org";
  $port=3306;
  $socket="";
  $user="danielcosta";
  $password="daniel123";
  $dbname="bd_daniel";

  $db_connection = new MySQLi($host, $user, $password, $dbname, $port);
  if($db_connection->connect_error){
    //echo "Connection Error (". $db_connection->connect_error. ")";
  }
  else{
    //echo "Connected to database";
    // Return name of current default database
    /*if ($result = $db_connection -> query("SELECT DATABASE()")) {
      $row = $result -> fetch_row();
      echo $row[0];
      $result -> close();
    }*/
  }

?>
