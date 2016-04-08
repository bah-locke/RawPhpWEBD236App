<?php
require_once "models/Db.inc";
require_once "include/util.inc";

abstract class Model {
	protected $id;
	
    public function __construct($id = null) {
        if ($id) {
            $this -> setId($id);
        }
    }

    public function getId() {
        return $this -> id;
    }

    public function setId($id) {
        $this -> id = $id;
        return $this;
    }

	// simple function to handle any query with no parameters...
	protected static function adHocQuery($q) {
		global $db;
		$st = $db -> prepare($q);
		$st -> execute();
		return $st -> fetchAll(PDO::FETCH_ASSOC);
	}

}
?>
