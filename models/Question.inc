<?php
include_once 'models/Model.inc';

class Question extends Model {

	private $user_id;
	private $title;
	private $content;
	private $tag;
	private $post_date;
	
	public function __construct($id, $user_id, $title, $content, $tag, $post_date = false) {
		parent::__construct($id);
		$this -> setUserId($user_id);
		$this -> setTitle($title);
		$this -> setContent($content);
		$this -> setTag($tag);
		$this -> setPostDate($post_date);
	}
	public function getUserId(){
		return $this -> user_id;
	}
	
	public function setUserId($user_id){
		$this -> user_id = $user_id;
		return $this;
	}
	
	public function getTitle(){
		return $this -> title;
	}
	
	public function setTitle($title){
		$this -> title = $title;
		return $this;
	}

	public function getContent(){
		return $this -> content;
	}
	
	public function setContent($content){
		$this -> content = $content;
		return $this;
	}	
	
	public function getTag(){
		return $this -> tag;
	}
	
	public function setTag($tag){
		$this -> tag = $tag;
		return $this;
	}
	
	public function getPostDate() {
		return $this -> post_date;
	}

	public function setPostDate($post_date){
		$this -> post_date = $post_date;
		return $this;
	}
	
	public static function findAllRecords() {
		$db = Db::getDb();

		$sql = 'SELECT * FROM questions ORDER BY post_date DESC';
		$statement = $db -> prepare($sql);
		$statement -> execute();
		$records = $statement -> fetchAll(PDO::FETCH_ASSOC);
		if (!$records){
			return false;
		}
		return self::makeQuestionsFromRows($records);
	}

	public static function findAllRecordsByTag($tag) {
		$db = Db::getDb();
		
		$tag = "%".$tag."%";
		
		$sql = 'SELECT * FROM questions WHERE lower(tag) LIKE :tag ORDER BY post_date DESC';
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':tag', $tag);
		$statement -> execute();
		$records = $statement -> fetchAll(PDO::FETCH_ASSOC);
		if (!$records){
			return false;
		}
		return self::makeQuestionsFromRows($records);
	}
	
	private static function makeQuestionFromRow($row) {
        $question = new Question($row['id'], $row['user_id'], $row['title'], $row['content'], $row['tag'], $row['post_date']);
        return $question;
    }
    
    private static function makeQuestionsFromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = self::makeQuestionFromRow($row);
        }
        return $result;
    }
	
	// Function to return a single record from table1 by record_id.... 
	public static function findRecordById($id) {
		$db = Db::getDb();
		
		$sql = "SELECT * FROM questions WHERE questions.id = :id ORDER BY post_date DESC";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':id', $id);
		$statement -> execute();
		$record = $statement -> fetch(PDO::FETCH_ASSOC);
		if (!$record){
			return false;
		}
		return self::makeQuestionFromRow($record);
	}	

	// Function to returns records by userid.... 
	public static function findRecordsByUserId($user_id) {
		$db = Db::getDb();
		
		$sql = "SELECT * FROM questions WHERE user_id = :user_id ORDER BY post_date DESC";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':user_id', $user_id);
		$statement -> execute();
		$records = $statement -> fetchAll(PDO::FETCH_ASSOC);
		if (!$records){
			return false;
		}
		return self::makeQuestionsFromRows($records);
	}	

	// Question Add Function...
	public function addRecord() {
		$db = Db::getDb();
		
		$sql = 'INSERT INTO questions (user_id, title, content, tag, post_date) VALUES (:user_id, :title, :content, :tag, CURRENT_DATE)';
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':user_id', $this -> user_id);
		$statement -> bindParam(':title', $this -> title);
		$statement -> bindParam(':content', $this -> content);
		$statement -> bindParam(':tag', $this -> tag);
		$statement -> execute();
		$this -> id = $db -> lastInsertId();
		return $this;
	}

	// Question Update Function...
	public function updateRecord() {
		$db = Db::getDb();
		
		$sql = 'UPDATE questions SET title = :title, content = :content, tag = :tag WHERE id = :id';
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':title', $this -> title);
		$statement -> bindParam(':content', $this -> content);
		$statement -> bindParam(':tag', $this -> tag);
		$statement -> bindParam(':id', $this -> id);
		$statement -> execute();
	}
	//Question delete by user id function...
	public static function deleteRecordByUserId($user_id) {
		$db = Db::getDb();

		$sql = "DELETE FROM questions WHERE user_id = :user_id";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':user_id', $user_id);
		$statement -> execute();
	}

	// Question Delete Function...
	public function deleteRecord() {
		$db = Db::getDb();

		$sql = "DELETE FROM questions WHERE id = :id";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':id', $this -> id);
		$statement -> execute();
	}
}
?>