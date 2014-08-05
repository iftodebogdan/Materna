<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/22/14
 * Time: 12:11 AM
 */

namespace Resources\Strings;

//Include helper class for debugging
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//Include Cfg class to access configuration data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include base class for Locale
require_once('LocaleBase.inc');

//Check if the correct locale is loaded
if(strcmp(Cfg::$locale, "en-us") == 0)
{
    class Locale extends LocaleBase {
        //set a localised string for each

	    //All views
        static $szPromotions        = "Promotions";
        static $szClothing          = "Clothing";
        static $szFootwear          = "Footwear";
        static $szToys              = "Toys";
        static $szFurniture         = "Furniture";
        static $szBaptism           = "Baptism";
        static $szContact           = "Contact";
	    static $szSearchButton      = "Search";
	    static $szSearchPlaceholder = "Product name";
	    static $szLogIn             = "Sign in";
	    static $szMyAccount         = "My account";
	    static $szLogOut            = "Sign out";
	    static $szSignUp            = "Sign up";
	    static $szAccount           = "Account";

	    //RegisterView
	    static $szRegistrationTitle             = "New User Registration Form";
	    static $szRequiredField                 = " indicates a required field";
	    static $szRegistrationUser              = "User name";
	    static $szRegistrationFullName          = "Full Name";
	    static $szRegistrationEmail             = "E-Mail Address";
	    static $szRegistrationRepeatEmail       = "Repeat E-Mail Address";
	    static $szRegistrationPassword          = "Password";
	    static $szRegistrationRepeatPassword    = "Repeat Password";
	    static $szRegistrationReset             = "Reset Form";
	    static $szRegistrationSubmit            = "   OK   ";
	    static $szUserNameInvalid               = "Invalid user ID! Valid characters are A-Z, a-z, 0-9 and '-._'";
	    static $szUserNameTaken                 = "User ID is already used!";
	    static $szFullNameInvalid               = "Your full name appears to be invalid! Names must have the correct case, must not contain consecutive spaces or dashes and not contain numerical or special characters. For further assistance, please contact support.";
	    static $szEmailInvalid                  = "Invalid E-mail!";
	    static $szEmailTaken                    = "Email is already used!";
	    static $szEmailNotMatch                 = "E-mails do not match!";
	    static $szPasswordInvalid               = "The password is invalid! It must be between 8 and 32 characters long and contain letters, numbers and/or punctuation marks.";
	    static $szPasswordNotMatch              = "The passwords do not match!";
	    static $szRegistrationSubmitted         = "You have successfully registered! Please check you email inbox for instructions on how to activate you account.";
	    static $szReturnToHome                  = "Return to home page";

	    //LoginView
	    static $szLoginTitle                    = "Log in";
	    static $szLoginUser                     = "User name";
	    static $szLoginPassword                 = "Password";
	    static $szLoginSubmit                   = "Log in";
	    static $szLoginForgotPassword           = "Forgot password?";
	    static $szLoginFailed                   = "User name and/or password are incorrect. Please try again.";
	    static $szNotActivated                  = "You have not activated your account yet. Please check your email inbox.";
    }
}
else
    //Wrong locale loaded, print a helpful debug message and die
    DbgHelper::PrintDbgMsgAndDie('Locale "' . Cfg::$locale . '" found in cfg.inc, but "' . basename(__FILE__) . '" has been loaded instead!', DbgHelper::RESOURCE);