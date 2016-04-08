<?php
include_once 'models/Model.inc';

class User extends Model {

	private $fname;
	private $lname;
	private $email;
	private $password;
	
	public function __construct($id, $fname, $lname, $email, $password){
		parent::__construct($id);
		$this -> setFirstName($fname);
		$this -> setLastName($lname);
		$this -> setEmail($email);
		$this -> setPassword($password);		
	}
	
	public function setFirstName($fname){
		$this -> fname = $fname;
		return $this;
	}
	public function getFirstName() {
		return $this ->fname;
	}
	
	public function setLastName($lname){
		$this -> lname = $lname;
		return $this;
	}	
	
	public function getLastName() {
		return $this ->lname;
	}
	
	public function getFullName() {
		return $this -> fname . ' ' . $this -> lname;
	}
	
	public function setEmail($email) {
		$this ->email = $email;
		return $this;
	}
	
	public function getEmail() {
		return $this ->email;
	}
	
	public function setPassword($password) {
		$this ->password = $password;
		return $this;
	}

	public function getPassword() {
		return $this ->password;
	}
	
	public static function findAllUsers() {
		$db = Db::getDb();

		$sql = 'SELECT * FROM users';
		$statement = $db -> prepare($sql);
		$statement -> execute();
		$users = $statement -> fetchAll(PDO::FETCH_ASSOC);
		if (!$users){
			return false;
		}
		return User::makeUsersFromRows($users);
	}

	public static function makeUserFromRow($row) {
        $user = new User($row['id'], $row['fname'], $row['lname'], $row['email'], $row['password']);
        return $user;
    }
    
    public static function makeUsersFromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = self::makeUserFromRow($row);
        }
        return $result;
    }
	
	// Function to return a single user from users by email.... 
	public static function findUserByEmail($email) {
		$db = Db::getDb();
		
		$sql = "SELECT * FROM users WHERE email = :email";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':email', $email);
		$statement -> execute();
		$user = $statement -> fetch(PDO::FETCH_ASSOC);
		if (!$user){
			return false;
		}
		return User::makeUserFromRow($user);
	}	

	// Function to return a single user from users by email.... 
	public static function findUserById($id) {
		$db = Db::getDb();
		
		$sql = "SELECT * FROM users WHERE id = :id";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':id', $id);
		$statement -> execute();
		$user = $statement -> fetch(PDO::FETCH_ASSOC);
		if (!$user){
			return false;
		}
		return User::makeUserFromRow($user);
	}	

	public static function isValidUser($email) {
		$userInfo = self::findUserByEmail($email);
		
		if (!$userInfo) {
			return false;
		}
		return true;
	}

	// Users Add Function...
	public function addUser() {
		$db = Db::getDb();
		
		$sql = 'INSERT INTO users (fname, lname, email, password) VALUES (:fname, :lname, :email, :password)';
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':fname', $this -> fname);
		$statement -> bindParam(':lname', $this -> lname);
		$statement -> bindParam(':email', $this -> email);
		$statement -> bindParam(':password', $this -> password);
		$statement -> execute();
		$this -> id = $db -> lastInsertId();
		return $this;
	}

	// Question Update Function...
	public function updateUser() {
		$db = Db::getDb();
		
		$sql = 'UPDATE users SET fname = :fname, lname = :lname, email = :email, password = :password WHERE id = :id';
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':id', $this -> id);
		$statement -> bindParam(':fname', $this -> fname);
		$statement -> bindParam(':lname', $this -> lname);
		$statement -> bindParam(':email', $this -> email);
		$statement -> bindParam(':password', $this -> password);
		$statement -> execute();
	}

	// User Delete Function...
	public function deleteUser() {
		$db = Db::getDb();

		$sql = "DELETE FROM users WHERE id = :id";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':id', $this -> id);
		$statement -> execute();
	}
}
?>