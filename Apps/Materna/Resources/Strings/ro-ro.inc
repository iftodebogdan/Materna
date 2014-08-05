<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/22/14
 * Time: 12:12 AM
 */

namespace Resources\Strings;

//Include debugging helper class
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//Include Cfg class to access configuration data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include base class for Locale
require_once('Resources/Strings/LocaleBase.inc');

//Check if the correct locale is loaded
if(strcmp(Cfg::$locale, "ro-ro") == 0)
{
    class Locale extends LocaleBase {
        //set a localised string for each string ID
        static $szPromotions        = "Promoții";
        static $szClothing          = "Articole îmbrăcăminte";
        static $szFootwear          = "Articole încălțăminte";
        static $szToys              = "Jucării";
        static $szFurniture         = "Mobilier camera copilului";
        static $szBaptism           = "Articole botez";
        static $szContact           = "Contact";
	    static $szSearchButton      = "Caută";
	    static $szSearchPlaceholder = "Denumire produs";
	    static $szLogIn             = "Conectare";
	    static $szMyAccount         = "Contul meu";
	    static $szLogOut            = "Deconectare";
	    static $szSignUp            = "Înregistrare";
	    static $szAccount           = "Cont";

	    //RegisterView
	    static $szRegistrationTitle             = "Formular înregistrare utilizator nou";
	    static $szRequiredField                 = " indică un câmp obligatoriu";
	    static $szRegistrationUser              = "Utilizator";
	    static $szRegistrationFullName          = "Nume întreg";
	    static $szRegistrationEmail             = "E-mail";
	    static $szRegistrationRepeatEmail       = "Repetă e-mail";
	    static $szRegistrationPassword          = "Parolă";
	    static $szRegistrationRepeatPassword    = "Repetă parolă";
	    static $szRegistrationReset             = "Resetare";
	    static $szRegistrationSubmit            = "Înregistrează-mă!";
	    static $szUserNameInvalid               = "Nume utilizator invalid! Caracterele valide sunt A-Z, a-z, 0-9 și '-._'";
	    static $szUserNameTaken                 = "Numele de utilizator este deja folosit!";
	    static $szFullNameInvalid               = "Numele pare a fi invalid! Fiecare nume trebuie sa înceapă cu literă mare, să nu conțină mai mult de un spațiu și/sau cratimă între nume și să nu conțină numere sau caractere speciale. Pentru asistență, folosiți <a href='Contact' style=\"color: white; font-weight: bold; text-decoration: underline\">formularul de contact</a>.";
	    static $szEmailInvalid                  = "E-mail invalid!";
	    static $szEmailTaken                    = "Adresa email este deja folosită!";
	    static $szEmailNotMatch                 = "E-mailurile nu se potrivesc!";
	    static $szPasswordInvalid               = "Parola e invalidă! Trebuie să aibă între 8 și 32 de caractere și să conțină litere, cifre și/sau semne de punctuație.";
	    static $szPasswordNotMatch              = "Parolele nu se potrivesc!";
	    static $szRegistrationSubmitted         = "V-ați înregistrat cu succes! Verificați-vă căsuța de email pentru instrucțiuni de activare a contului.";
	    static $szReturnToHome                  = "Reveniți la pagina principală";

	    //LoginView
	    static $szLoginTitle                    = "Autentificare utilizator";
	    static $szLoginUser                     = "Utilizator";
	    static $szLoginPassword                 = "Parolă";
	    static $szLoginSubmit                   = "Autentificare";
	    static $szLoginForgotPassword           = "Ați uitat parola?";
	    static $szLoginFailed                   = "Utilizatorul și/sau parola sunt greșite. Vă rugăm să încercați din nou.";
	    static $szNotActivated                  = "Încă nu v-ați activat contul. Verificați căsuța de email. Pentru asistență, folosiți <a href='Contact' style=\"color: white; font-weight: bold; text-decoration: underline\">formularul de contact</a>.";
    }
}
else
    //Wrong locale loaded, print a helpful debug message and die
    DbgHelper::PrintDbgMsgAndDie('Locale "' . Cfg::$locale . '" found in cfg.inc, but "' . basename(__FILE__) . '" has been loaded instead!', DbgHelper::RESOURCE);