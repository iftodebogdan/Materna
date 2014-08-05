<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 04/08/14
 * Time: 23:30
 */

namespace Views;

//Include global config data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include theme class
require_once('Apps/' . Cfg::$appTitle . '/Resources/Themes/' . Cfg::$appTheme . 'Theme.inc');
use Resources\Themes\GuiAlignment;
use Resources\Themes\GuiBox;
use Resources\Themes\Theme as Theme;

//Include Model class
require_once('Apps/' . Cfg::$appTitle . '/Models/LoginModel.inc');
use Models\LoginModel as Model;

//Include Controller class
require_once('Apps/' . Cfg::$appTitle . '/Controllers/LoginController.inc');
use Controllers\LoginController as Controller;

//Include debugging helper class
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//Include localised string resources
require_once('Apps/' . Cfg::$appTitle . '/Resources/Strings/' . Cfg::$locale . '.inc');
use Resources\Strings\Locale as Locale;

//Include cryptography helpers
require_once('Utils/Cryptography/CryptographyHelper.inc');
use Utils\Cryptography\CryptographyHelper;

//Include BaseView
require_once('Views/ViewBase.inc');

class LoginView extends ViewBase
{
	private $linkList;

	function Init()
	{
		CryptographyHelper::RequireSSL();

		//Retrieve header links
		$this->linkList= array();
		Model::GetHeaderLinks($this->linkList);
	}

	function Draw()
	{
		//Draw the view
		$response = Controller::TryLoginAndGetUserData($userData);
		if($response == Controller::USER_LOGGED_IN)
			header("Location:Home");
		else
			$this->DrawLoginForm($response);
	}

	private function DrawLoginForm($response)
	{
		if(empty($this->linkList))
		{
			DbgHelper::PrintDbgMsg("HomeView: header link list is empty!", DbgHelper::GUI);
			return;
		}

		Theme::GuiBeginDraw();
		Theme::GuiDrawHeader($this->linkList);

		Theme::GuiDrawContent(new GuiBox(0, 0, 1006, 16), "", "", "main-header");
		Theme::GuiDrawContent(new GuiBox(0, 0, 1006, 0), $this->CreateLoginForm($response), "", "main-center");
		Theme::GuiDrawContent(new GuiBox(0, 0, 1006, 16), "", "", "main-footer");

		Theme::GuiDrawFooter();
		Theme::GuiEndDraw();
	}

	private function CreateLoginForm($validationResponse = null)
	{
		$ret = "
			</br>
			<h3>" . Locale::ReturnStrById("szLoginTitle") . "</h3>";

		if($validationResponse)
		{
			$ret .= "
				<table width=\"500\" bgcolor=\"red\" align=\"center\" border=\"0\" cellpadding=\"5\" cellspacing=\"5\" style=\"text-align: left; color: white; border-radius: 6px;\">
			";

			if($validationResponse & Controller::USER_LOGIN_FAILED)
				$ret .= "
					<tr>
						<td>
							<b>&bull; " . Locale::ReturnStrById("szLoginFailed") . "</b>
						</td>
					</tr>
				";

			if($validationResponse & Controller::USER_NOT_ACTIVATED)
				$ret .= "
					<tr>
						<td>
							<b>&bull; " . Locale::ReturnStrById("szNotActivated") . "</b>
						</td>
					</tr>
				";

			$ret .= "
				</table><br/>
			";
		}

		$ret .= "
		    <form method=\"post\" action=\"$_SERVER[REQUEST_URI]\">

			<table border=\"0\" cellpadding=\"0\" cellspacing=\"5\" align=\"center\">

				<tr>

					<!--[if lte IE 9]>
					<td align=\"right\">

						<p>" . Locale::ReturnStrById("szLoginUser") . "</p>

					</td>
					<![endif]-->

					<td>

						<input name=\"UserName\" type=\"text\" maxlength=\"100\" size=\"35\" placeholder=\"" . Locale::ReturnStrById("szLoginUser") . "\" />

					</td>

				</tr>

				<tr>

					<!--[if lte IE 9]>
					<td align=\"right\">

						<p>" . Locale::ReturnStrById("szLoginPassword") . "</p>

					</td>
					<![endif]-->

					<td>

						<input name=\"Password\" type=\"password\" maxlength=\"32\" size=\"35\" placeholder=\"" . Locale::ReturnStrById("szLoginPassword") . "\" />

					</td>

				</tr>

				<tr>

					<td align=\"right\" colspan=\"2\">

						<hr noshade=\"noshade\" />

						<a href=\"Recover\">" . Locale::ReturnStrById("szLoginForgotPassword") . "<a/>

						<input type=\"submit\" name=\"Submit\" value=\"" . Locale::ReturnStrById("szLoginSubmit") . "\" />

					</td>

				</tr>

			</table>

			</form>
			</br></br>
		";

		return $ret;
	}
} 