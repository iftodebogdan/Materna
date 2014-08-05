<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 26/07/14
 * Time: 00:23
 */

namespace Controllers;

//Include global config data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include Model class
require_once('Apps/' . Cfg::$appTitle . '/Models/RegisterModel.inc');
use Models\RegisterModel as Model;

//Include global controller
require_once('Apps/' . Cfg::$appTitle . '/Controllers/CommonController.inc');

class RegisterController extends CommonController
{
	private $model;

	const REGISTRATION_USER_ID_INVALID      = 1;    //1 << 0
	const REGISTRATION_USER_ID_TAKEN        = 2;    //1 << 1
	const REGISTRATION_FULL_NAME_INVALID    = 4;    //1 << 2
	const REGISTRATION_EMAIL_INVALID        = 8;    //1 << 3
	const REGISTRATION_EMAIL_TAKEN          = 16;   //1 << 4
	const REGISTRATION_EMAIL_NOT_MATCH      = 32;   //1 << 5
	const REGISTRATION_PASSWORD_INVALID     = 64;   //1 << 6
	const REGISTRATION_PASSWORD_NOT_MATCH   = 128;  //1 << 7

	function __construct(Model $model)
	{
		$this->model = $model;
	}

	public function RetrieveRegistrationData(&$data = array())
	{
		$data = array(
			"UserName"            => $_POST['UserName'],
			"FullName"          => $_POST['FullName'],
			"Email"             => $_POST['Email'],
			"RepeatEmail"       => $_POST['RepeatEmail'],
			"Password"          => $_POST['Password'],
			"RepeatPassword"    => $_POST['RepeatPassword']
		);

		if( !array_key_exists("UserName", $_POST) ||
			!array_key_exists("FullName", $_POST) ||
			!array_key_exists("Email", $_POST) ||
			!array_key_exists("RepeatEmail", $_POST) ||
			!array_key_exists("Password", $_POST) ||
			!array_key_exists("RepeatPassword", $_POST) )
				return false;

		return true;
	}

	public function ValidateRegistrationData(&$data = array())
	{
		$filters = array(
			"UserName"            => array(
				"filter"   => FILTER_VALIDATE_REGEXP,
				"options"   => array(
					"regexp"    => '/^[A-Za-z0-9-._]+$/')
			),
		    "FullName"          => array(
				"filter"   => FILTER_VALIDATE_REGEXP,
				"options"   => array(
					"regexp"    => '/^((?<![a-z])[A-Z]{1}[a-z]{1,35}(\s(?=[A-Z-]))?(-(?=[A-Z\s]))?((?<=-)\s)?){2,}$/')
			),
		    "Email"             => FILTER_VALIDATE_EMAIL,
		    "RepeatEmail"       => FILTER_VALIDATE_EMAIL,
		    "Password"          => FILTER_SANITIZE_STRING,
		    "RepeatPassword"    => FILTER_SANITIZE_STRING
		);

		$data = filter_var_array($data, $filters);

		$ret = 0;
		//Verify User ID for validity and uniqueness
		if(!$data['UserName'])
			$ret |= self::REGISTRATION_USER_ID_INVALID;
		else
			if($this->model->IsUserNameTaken($data['UserName']))
				$ret |= self::REGISTRATION_USER_ID_TAKEN;
		//Verify full name for validity
		if(!$data['FullName'])
			$ret |= self::REGISTRATION_FULL_NAME_INVALID;
		//Verify email for validity, uniqueness and if it matches the second email input
		if(!$data['Email'])
			$ret |= self::REGISTRATION_EMAIL_INVALID;
		else
			if($this->model->IsEmailTaken($data['Email']))
				$ret |= self::REGISTRATION_EMAIL_TAKEN;
			else
				if(strcmp($data['Email'], $data['RepeatEmail']) != 0)
					$ret |= self::REGISTRATION_EMAIL_NOT_MATCH;
		//Verify password validity and if it matches the second password input
		if(!$data['Password'] || strlen($data['Password']) < 8 || strlen($data['Password']) > 32)
			$ret |= self::REGISTRATION_PASSWORD_INVALID;
		else
			if(strcmp($data['Password'], $data['RepeatPassword']) != 0)
				$ret |= self::REGISTRATION_PASSWORD_NOT_MATCH;

		return $ret;
	}

	public function SubmitRegistrationData($data = array())
	{
		if( !empty($data) &&
			array_key_exists("UserName", $_POST) &&
			array_key_exists("FullName", $_POST) &&
			array_key_exists("Email", $_POST) &&
			array_key_exists("RepeatEmail", $_POST) &&
			array_key_exists("Password", $_POST) &&
			array_key_exists("RepeatPassword", $_POST) )
				return $this->model->AddNewUser($data);
		else
			return false;
	}
} 