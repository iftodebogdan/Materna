<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 26/07/14
 * Time: 21:23
 */

namespace Utils\Cryptography;

//Include debugging helper class
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//Include global config data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

class PasswordAlgorithm
{
	const PASSWORD_DEFAULT  = PASSWORD_DEFAULT;
	const PASSWORD_BCRYPT   = PASSWORD_BCRYPT;
}

class CryptographyHelper
{
	public static function GetPasswordInfo($hash = "")
	{
		$ret = password_get_info($hash);

		if(empty($ret))
			DbgHelper::PrintDbgMsg("CRYPTOGRAPHY: No information could be retrieved about this hash!", DbgHelper::SYSTEM);

		return $ret;
	}

	public static function HashPassword($password = "", $algo = PasswordAlgorithm::PASSWORD_DEFAULT, $options = array())
	{
		if(empty($options))
			$options = array('cost' => Cfg::$algorithmCost);

		$ret = password_hash($password, $algo, $options);

		if(empty($ret))
			DbgHelper::PrintDbgMsg("CRYPTOGRAPHY: Password couldn't be hashed!", DbgHelper::SYSTEM);

		return $ret;
	}

	public static function CheckPasswordNeedsRehash($hash = "", $algo = PasswordAlgorithm::PASSWORD_DEFAULT, $options = array())
	{
		if(empty($options))
			$options = array('cost' => Cfg::$algorithmCost);

		$ret = password_needs_rehash($hash, $algo, $options);

		if(is_null($ret))
			DbgHelper::PrintDbgMsg("CRYPTOGRAPHY: Password couldn't be checked for rehashing!", DbgHelper::SYSTEM);

		return $ret;
	}

	public static function VerifyPassword($password = "", $hash = "")
	{
		$ret = password_verify($password, $hash);

		if(is_null($ret))
			DbgHelper::PrintDbgMsg("CRYPTOGRAPHY: Password couldn't be verified!", DbgHelper::SYSTEM);

		return $ret;
	}

	public static function Encrypt($text, $key = "")
	{
		if(empty($key))
			$key = Cfg::$encryptionKey;

		$encrypt = serialize($text);
	    $iv = mcrypt_create_iv(mcrypt_get_iv_size(MCRYPT_RIJNDAEL_256, MCRYPT_MODE_CBC), MCRYPT_DEV_URANDOM);
	    $key = pack('H*', $key);
	    $mac = hash_hmac('sha256', $encrypt, substr(bin2hex($key), -32));
	    $passcrypt = mcrypt_encrypt(MCRYPT_RIJNDAEL_256, $key, $encrypt.$mac, MCRYPT_MODE_CBC, $iv);
	    $encoded = base64_encode($passcrypt).'|'.base64_encode($iv);
	    return $encoded;
	}

	public static function Decrypt($encryptedText, $key = "")
	{
		if(empty($key))
			$key = Cfg::$encryptionKey;

		$decrypt = explode('|', $encryptedText);
		$decoded = base64_decode($decrypt[0]);
		$iv = base64_decode($decrypt[1]);
		if(strlen($iv)!==mcrypt_get_iv_size(MCRYPT_RIJNDAEL_256, MCRYPT_MODE_CBC)){ return false; }
		$key = pack('H*', $key);
		$decrypted = trim(mcrypt_decrypt(MCRYPT_RIJNDAEL_256, $key, $decoded, MCRYPT_MODE_CBC, $iv));
		$mac = substr($decrypted, -64);
		$decrypted = substr($decrypted, 0, -64);
		$calcmac = hash_hmac('sha256', $decrypted, substr(bin2hex($key), -32));
		if($calcmac!==$mac){ return false; }
		$decrypted = unserialize($decrypted);
		return $decrypted;
	}

	public static function RequireSSL($activate = true)
	{
		if($activate && Cfg::$permitSSL)
		{
			if(!array_key_exists("HTTPS", $_SERVER) || $_SERVER["HTTPS"] != "on")
			{
				header("Location: https://" . $_SERVER["HTTP_HOST"] . $_SERVER["REQUEST_URI"]);
				exit();
			}
		}
		else
		{
			if(array_key_exists("HTTPS", $_SERVER) && $_SERVER["HTTPS"] == "on")
			{
				header("Location: http://" . $_SERVER["HTTP_HOST"] . $_SERVER["REQUEST_URI"]);
				exit();
			}
		}
	}
} 