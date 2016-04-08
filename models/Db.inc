<?php
class Db {
    public static function getDb() {
		try {
			$db = new PDO('sqlite:QUESTIONS.db3');
		} catch (PDOException $e) {
			die("Could not open database. " . $e->getMessage());
		}
		return $db;
    }
}
?>
