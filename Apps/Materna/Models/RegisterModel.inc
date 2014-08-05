<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 26/07/14
 * Time: 00:23
 */

namespace Models;

//Include global config data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include SQL helpers
require_once('Utils/SQL/SQLHelper.inc');
use Utils\SQL\SQLHelper as SQLHelper;

//Include cryptography helpers
require_once('Utils/Cryptography/CryptographyHelper.inc');
use Utils\Cryptography\CryptographyHelper;

//Necessary for retrieving common data from the DB
require_once('Apps/' . Cfg::$appTitle . '/Models/CommonModel.inc');

//Include debugging helper class
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

class RegisterModel extends CommonModel
{
	public function IsUserNameTaken($userName)
	{
		$sql = new SQLHelper();
		$sql->Connect();
		$userName = $sql->Sanitize($userName);
		$result = $sql->Query("SELECT UserName FROM UserInformation WHERE UserName = '$userName'");
		$sql->Disconnect();

		$ret = mysqli_num_rows($result) != 0 ? true : false;
		return $ret;
	}

	public function IsEmailTaken($email)
	{
		$sql = new SQLHelper();
		$sql->Connect();
		$email = $sql->Sanitize($email);
		$result = $sql->Query("SELECT Email FROM UserInformation WHERE Email = '$email'");
		$sql->Disconnect();

		$ret = mysqli_num_rows($result) != 0 ? true : false;
		return $ret;
	}

	public function AddNewUser($data)
	{
		$sql = new SQLHelper();
		$sql->Connect();

		foreach($data as $index => $value)
			$data[$index] = $sql->Sanitize($value);

		$activationCode = md5(time());
		$data['Password'] = CryptographyHelper::HashPassword($data['Password']);

		$result = $sql->Query("
			INSERT INTO UserInformation
					(UserName, Password, FullName, Email, ActivationCode)
			VALUES	('" . $data['UserName'] . "', '" . $data['Password'] . "', '" . $data['FullName'] . "', '" . $data['Email'] . "', '$activationCode')
		");

		$sql->Disconnect();

		if($result)
			return true;

		DbgHelper::PrintDbgMsg("Could not add new user to the database!", DbgHelper::MODEL);
		return false;
	}
} 