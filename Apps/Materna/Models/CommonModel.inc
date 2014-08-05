<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 24/04/14
 * Time: 19:34
 */

namespace Models;

//Include SQL helpers
require_once('Utils/SQL/SQLHelper.inc');
use Utils\SQL\SQLHelper as SQLHelper;

//Include cryptography helpers
require_once('Utils/Cryptography/CryptographyHelper.inc');
use Utils\Cryptography\CryptographyHelper;

//Include ModelBase
require_once('Models/ModelBase.inc');

//A model for common data that can be retrieved/manipulated by any View/Controller
abstract class CommonModel extends ModelBase
{
    //Retrieve header link list information from the DB
    public static function GetHeaderLinks(&$links)
    {
        //create new SQLHelper class
        $sql = new SQLHelper();
        //connect to the DB with the info from cfg.inc
        $sql->Connect();
        //execute the query
        $result = $sql->Query('SELECT LinkText AS text, LinkHref AS href FROM HeaderLinks GROUP BY LinkIdx ASC');
        //disconnect from the DB
        $sql->Disconnect();

        //insert link info in array
        while($result && $row = mysqli_fetch_array($result)) {
            $links[] = $row;
        }

        //return number of rows retrieved
        $rowCount = $result ? mysqli_num_rows($result) : 0;
        return $rowCount;
    }

	//Retrieve user data with supplied user name
	public static function GetUserData($userName)
	{
		if($userName)
		{
			$sql = new SQLHelper();
			$sql->Connect();
			$result = $sql->Query("SELECT * FROM UserInformation WHERE UserName = '$userName'");
			$sql->Disconnect();

			$userData = array();
			if($result && $row = mysqli_fetch_array($result))
				$userData[] = $row;

			return (!empty($userData) ? $userData[0] : false);
		}

		return false;
	}

	//Set a user's password
	public static function SetUserPassword($userName, $password)
	{
		if($userName && $password)
		{
			$sql = new SQLHelper();
			$sql->Connect();
			$hash = CryptographyHelper::HashPassword($password);
			$result = $sql->Query("UPDATE UserInformation SET Password = '$hash' WHERE UserName = '$userName'");

			return ($result ? true : false);
		}

		return false;
	}
}