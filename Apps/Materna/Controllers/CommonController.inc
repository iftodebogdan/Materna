<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 01/08/14
 * Time: 00:12
 */

namespace Controllers;

//Include global config data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include Model class
require_once('Apps/' . Cfg::$appTitle . '/Models/CommonModel.inc');
use Models\CommonModel as CommonModel;

//Include cryptography helpers
require_once('Utils/Cryptography/CryptographyHelper.inc');
use Utils\Cryptography\CryptographyHelper;

//Include debug functions
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//Include ControllerBase
require_once('Controllers/ControllerBase.inc');

class CommonController extends ControllerBase
{
	const USER_NOT_LOGGED_IN    = 0;
	const USER_LOGIN_FAILED     = 1;
	const USER_NOT_ACTIVATED    = 2;
	const USER_LOGGED_IN        = 3;

	public static function RehashUserPassword()
	{
		if(isset($_SESSION['UserName']) && isset($_SESSION['Password']))
			return CommonModel::SetUserPassword($_SESSION['UserName'], CryptographyHelper::Decrypt($_SESSION['Password']));
		else
			return false;
	}

	public static function TryLoginAndGetUserData(&$retUserData)
	{
		$retUserData = null;
		$userName = (isset($_POST['UserName']) ? $_POST['UserName'] : (isset($_SESSION['UserName']) ? $_SESSION['UserName'] : ""));
		$password = (isset($_POST['Password']) ? $_POST['Password'] : (isset($_SESSION['Password']) ? CryptographyHelper::Decrypt($_SESSION['Password']) : ""));

		unset($_SESSION['UserName']);
		unset($_SESSION['Password']);

		if($userName && $password && $userData = CommonModel::GetUserData($userName))
		{
			if(CryptographyHelper::VerifyPassword($password, $userData["Password"]))
			{
				if($userData["IsActivated"])
				{
					$_SESSION['UserName'] = $userName;
					$_SESSION['Password'] = CryptographyHelper::Encrypt($password);

					if(CryptographyHelper::CheckPasswordNeedsRehash($userData["Password"]) && !self::RehashUserPassword())
						DbgHelper::PrintDbgMsg("Couldn't rehash user password", DbgHelper::CONTROLLER);

					$retUserData = $userData;
					return self::USER_LOGGED_IN;
				}
				else
					return self::USER_NOT_ACTIVATED;
			}
			else
				return self::USER_LOGIN_FAILED;
		}

		return self::USER_NOT_LOGGED_IN;
	}

	public static function LogoutUser()
	{
		unset($_SESSION['UserName']);
		unset($_SESSION['Password']);
	}
} 