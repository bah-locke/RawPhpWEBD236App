<?php
include_once 'models/Model.inc';

class Answer extends Model {

	private $user_id;
	private $question_id;
	private $answer_text;
	private $answer_date;
	
	public function __construct($id, $user_id, $question_id, $answer_text, $answer_date = false) {
		parent::__construct($id);
		$this -> setUserId($user_id);
		$this -> setQuestionId($question_id);
		$this -> setAnswerText($answer_text);
		$this -> setAnswerDate($answer_date);
	}
	public function getUserId(){
		return $this -> user_id;
	}
	
	public function setUserId($user_id){
		$this -> user_id = $user_id;
		return $this;
	}
	
	public function getQuestionId(){
		return $this -> question_id;
	}
	
	public function setQuestionId($question_id){
		$this -> question_id = $question_id;
		return $this;
	}

	public function getAnswerText(){
		return $this -> answer_text;
	}
	
	public function setAnswerText($answer_text){
		$this -> answer_text = $answer_text;
		return $this;
	}	
	
	public function getAnswerDate() {
		return $this -> answer_date;
	}

	public function setAnswerDate($answer_date){
		$this -> answer_date = $answer_date;
		return $this;
	}
	
	public static function findAllAnswers() {
		$db = Db::getDb();

		$sql = 'SELECT * FROM answers ORDER BY answer_date DESC';
		$statement = $db -> prepare($sql);
		$statement -> execute();
		$answers = $statement -> fetchAll(PDO::FETCH_ASSOC);
		if (!$answers){
			return false;
		}
		return self::makeAnswersFromRows($answers);
	}
	
	private static function makeAnswerFromRow($row) {
        $answer = new Answer($row['id'], $row['user_id'], $row['question_id'], $row['answer_text'], $row['answer_date']);
        return $answer;
    }
    
    private static function makeAnswersFromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = self::makeAnswerFromRow($row);
        }
        return $result;
    }
	
	// Function to return a single answer from table1 by answer_id.... 
	public static function findAnswerById($id) {
		$db = Db::getDb();
		
		$sql = "SELECT * FROM answers WHERE answers.id = :id ORDER BY answer_date DESC";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':id', $id);
		$statement -> execute();
		$answer = $statement -> fetch(PDO::FETCH_ASSOC);
		if (!$answer){
			return false;
		}
		return self::makeAnswerFromRow($answer);
	}	

	// Function to returns answers by userid.... 
	public static function findAnswersByUserId($user_id) {
		$db = Db::getDB();
		
		$sql = "SELECT * FROM answers WHERE user_id = :user_id ORDER BY answer_date DESC";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':user_id', $user_id);
		$statement -> execute();
		$answers = $statement -> fetchAll(PDO::FETCH_ASSOC);
		if (!$answers){
			return false;
		}
		return self::makeAnswersFromRows($answers);
	}	

	// Function to returns answers by userid.... 
	public static function findAnswersByQuestionId($question_id) {
		$db = Db::getDB();
		
		$sql = "SELECT * FROM answers WHERE question_id = :question_id ORDER BY answer_date DESC";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':question_id', $question_id);
		$statement -> execute();
		$answers = $statement -> fetchAll(PDO::FETCH_ASSOC);
		if (!$answers){
			return false;
		}
		return self::makeAnswersFromRows($answers);
	}	
	
	// Answer Add Function...
	public function addAnswer() {
		$db = Db::getDB();
		
		$sql = 'INSERT INTO answers (user_id, question_id, answer_text, answer_date) VALUES (:user_id, :question_id, :answer_text, CURRENT_DATE)';
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':user_id', $this -> user_id);
		$statement -> bindParam(':question_id', $this -> question_id);
		$statement -> bindParam(':answer_text', $this -> answer_text);
		$statement -> execute();
		$this -> id = $db -> lastInsertId();
		return $this;
	}

	//Answer delete by user id function...
	public static function deleteAnswerByUserId($user_id) {
		$db = Db::getDB();

		$sql = "DELETE FROM answers WHERE user_id = :user_id";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':user_id', $user_id);
		$statement -> execute();
	}

	//Answer delete by question id function...
	public static function deleteAnswerByQuestionId($question_id) {
		$db = Db::getDB();

		$sql = "DELETE FROM answers WHERE question_id = :question_id";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':question_id', $question_id);
		$statement -> execute();
	}
	
	// Answer Delete Function...
	public function deleteAnswer() {
		$db = Db::getDB();

		$sql = "DELETE FROM answers WHERE id = :id";
		$statement = $db -> prepare($sql);
		$statement -> bindParam(':id', $this -> id);
		$statement -> execute();
	}
}
?>