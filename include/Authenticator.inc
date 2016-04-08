<?php
include_once 'models/Model.inc';
include_once 'models/Permission.inc';
include_once 'include/util.inc';
include_once 'include/Logger.inc';

class Authenticator {

    private $cache;
    private static $instance;

    // @formatter:off
    const PERMS_QUERY =
        'SELECT DISTINCT permissions.id as id,
                permissions.name as name                
		FROM
						users                

		INNER JOIN      usergroups
		ON              users.id = usergroups.userId

		INNER JOIN      groups
		ON              usergroups.groupId = groups.id

		INNER JOIN      grouppermissions
		ON              groups.id = grouppermissions.groupId

		INNER JOIN      permissions
		ON              grouppermissions.permissionId = permissions.id 

		WHERE
						users.id = :param';
    // @formatter:on

    private function __construct() {
        $cache = array();
    }

    public static function instance() {
        if (!isset(self::$instance)) {
            self::$instance = new Authenticator();
        }
        return self::$instance;
    }

    private function realUserId($userId) {
        if (isset($userId) && is_numeric($userId)) {
            return $userId;
        }
        if (gettype($userId) == 'object') {
            return $userId -> getId();
        }
        return currentUser();
    }

    public function can($permissionKey, $userId = false) {
        $userId = $this -> realUserId($userId);
        $permissions = $this -> permissionsFor($userId);
        foreach ($permissions as $permission) {
            if ($permission -> getName() === $permissionKey) {
                return true;
            }
        }
        return false;
    }

    private function permissionsFor($userId) {
        if (!isset($this -> cache[$userId])) {
            $db = Db::getDb();
			
            $stQuery = $db -> prepare(self::PERMS_QUERY);
            $stQuery -> bindParam(':param', $userId);
            $stQuery -> execute();
            $this -> cache[$userId] = Permission::fromRows($stQuery -> fetchAll(PDO::FETCH_ASSOC));
			
		}
		
       return $this -> cache[$userId];
    }

    public function ensure($permissionKey, $userId = false) {
        if (!$this -> can($permissionKey, $userId)) {
            $userId = $this -> realUserId($userId);
            Logger::instance() -> warn("User $userId attempted unauthorized operation $permissionKey");
            die("You do not have permission to access this resource.  This attempt has been logged.");
        }
    }

}
?>