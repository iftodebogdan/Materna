<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 26/07/14
 * Time: 00:15
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
require_once('Apps/' . Cfg::$appTitle . '/Models/RegisterModel.inc');
use Models\RegisterModel as Model;

//Include Controller class
require_once('Apps/' . Cfg::$appTitle . '/Controllers/RegisterController.inc');
use Controllers\RegisterController as Controller;

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

class RegisterView extends ViewBase
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
		if(!isset($_POST['Submit']))
			$this->DrawRegistrationForm();
		else
			$this->DrawRegistrationResponse();
	}

	private function DrawRegistrationForm()
	{
		if(empty($this->linkList))
		{
			DbgHelper::PrintDbgMsg("HomeView: header link list is empty!", DbgHelper::GUI);
			return;
		}

		Theme::GuiBeginDraw();
		Theme::GuiDrawHeader($this->linkList);

		Theme::GuiDrawContent(new GuiBox(0, 0, 1006, 16), "", "", "main-header");
		Theme::GuiDrawContent(new GuiBox(0, 0, 1006, 0), $this->CreateRegistrationForm(), "", "main-center");
		Theme::GuiDrawContent(new GuiBox(0, 0, 1006, 16), "", "", "main-footer");

		Theme::GuiDrawFooter();
		Theme::GuiEndDraw();
	}

	private function DrawRegistrationResponse()
	{
		if(empty($this->linkList))
		{
			DbgHelper::PrintDbgMsg("HomeView: header link list is empty!", DbgHelper::GUI);
			return;
		}

		Theme::GuiBeginDraw();
		Theme::GuiDrawHeader($this->linkList);

		if(!$this->controller->RetrieveRegistrationData($data))
			DbgHelper::PrintDbgMsgAndDie("Could not retrieve registration data!", DbgHelper::VIEW);

		DbgHelper::PrintDbgMsg("Before: " . var_export($data, true), DbgHelper::VIEW);
		$response = $this->controller->ValidateRegistrationData($data);
		DbgHelper::PrintDbgMsg("After: " . var_export($data, true), DbgHelper::VIEW);

		if($response != 0)
		{
			Theme::GuiDrawContent(new GuiBox(0, 0, 1006, 16), "", "", "main-header");
			Theme::GuiDrawContent(new GuiBox(0, 0, 1006, 0), $this->CreateRegistrationForm($response), "", "main-center");
			Theme::GuiDrawContent(new GuiBox(0, 0, 1006, 16), "", "", "main-footer");
		}
		else
		{
			$this->controller->SubmitRegistrationData($data);
			Theme::GuiDrawContent(new GuiBox(0, 0, 1006, 16), "", "", "main-header");
			Theme::GuiDrawContent(new GuiBox(0, 0, 1006, 0),
			                      "<br/><br/>
			                      <h3>" . Locale::ReturnStrById("szRegistrationSubmitted") . "</h3><br/><br/>
			                      <center><a href=\"Home\">" . Locale::ReturnStrById("szReturnToHome") . "</a></center>
			                      <br/><br/>
			                      ", "", "main-center");
			Theme::GuiDrawContent(new GuiBox(0, 0, 1006, 16), "", "", "main-footer");
		}

		Theme::GuiDrawFooter();
		Theme::GuiEndDraw();
	}

	private function CreateRegistrationForm($validationResponse = null)
	{
		$ret = "
			</br>
			<h3>" . Locale::ReturnStrById("szRegistrationTitle") . "</h3>

			  <p><font color=\"orangered\" size=\"+1\"><tt><b>*</b></tt></font>" . Locale::ReturnStrById("szRequiredField") . "</p>";

		if($validationResponse)
		{
			$ret .= "
				<table width=\"500\" bgcolor=\"red\" align=\"center\" border=\"0\" cellpadding=\"5\" cellspacing=\"5\" style=\"text-align: left; color: white; border-radius: 6px;\">
			";

			if($validationResponse & Controller::REGISTRATION_USER_ID_INVALID)
				$ret .= "
					<tr>
						<td>
							<b>&bull; " . Locale::ReturnStrById("szUserNameInvalid") . "</b>
						</td>
					</tr>
				";

			if($validationResponse & Controller::REGISTRATION_USER_ID_TAKEN)
				$ret .= "
					<tr>
						<td>
							<b>&bull; " . Locale::ReturnStrById("szUserNameTaken") . "</b>
						</td>
					</tr>
				";

			if($validationResponse & Controller::REGISTRATION_FULL_NAME_INVALID)
				$ret .= "
					<tr>
						<td>
							<b>&bull; " . Locale::ReturnStrById("szFullNameInvalid") . "</b>
						</td>
					</tr>
				";

			if($validationResponse & Controller::REGISTRATION_EMAIL_INVALID)
				$ret .= "
					<tr>
						<td>
							<b>&bull; " . Locale::ReturnStrById("szEmailInvalid") . "</b>
						</td>
					</tr>
				";

			if($validationResponse & Controller::REGISTRATION_EMAIL_TAKEN)
				$ret .= "
					<tr>
						<td>
							<b>&bull; " . Locale::ReturnStrById("szEmailTaken") . "</b>
						</td>
					</tr>
				";

			if($validationResponse & Controller::REGISTRATION_EMAIL_NOT_MATCH)
				$ret .= "
					<tr>
						<td>
							<b>&bull; " . Locale::ReturnStrById("szEmailNotMatch") . "</b>
						</td>
					</tr>
				";

			if($validationResponse & Controller::REGISTRATION_PASSWORD_INVALID)
				$ret .= "
					<tr>
						<td>
							<b>&bull; " . Locale::ReturnStrById("szPasswordInvalid") . "</b>
						</td>
					</tr>
				";

			if($validationResponse & Controller::REGISTRATION_PASSWORD_NOT_MATCH)
				$ret .= "
					<tr>
						<td>
							<b>&bull; " . Locale::ReturnStrById("szPasswordNotMatch") . "</b>
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

						<p>" . Locale::ReturnStrById("szRegistrationUser") . "</p>

					</td>
					<![endif]-->

					<td>

						<input " . ($validationResponse & (Controller::REGISTRATION_USER_ID_INVALID | Controller::REGISTRATION_USER_ID_TAKEN) ? "style=\"border-color:red;\"" : "") . " value=\"" . (array_key_exists('UserName', $_POST) ? filter_var($_POST['UserName'], FILTER_SANITIZE_STRING) : "") . "\" name=\"UserName\" type=\"text\" maxlength=\"100\" size=\"35\" placeholder=\"" . Locale::ReturnStrById("szRegistrationUser") . "\" />

						<font color=\"orangered\" size=\"+1\"><tt><b>*</b></tt></font>

					</td>

				</tr>

				<tr>

					<!--[if lte IE 9]>
					<td align=\"right\">

						<p>" . Locale::ReturnStrById("szRegistrationFullName") . "</p>

					</td>
					<![endif]-->

					<td>

						<input " . ($validationResponse & Controller::REGISTRATION_FULL_NAME_INVALID ? "style=\"border-color:red;\"" : "") . " value=\"" . (array_key_exists('FullName', $_POST) ? filter_var($_POST['FullName'], FILTER_SANITIZE_STRING) : "") . "\" name=\"FullName\" type=\"text\" maxlength=\"100\" size=\"35\" placeholder=\"" . Locale::ReturnStrById("szRegistrationFullName") . "\" />

						<font color=\"orangered\" size=\"+1\"><tt><b>*</b></tt></font>

					</td>

				</tr>

				<tr>

					<!--[if lte IE 9]>
					<td align=\"right\">

						<p>" . Locale::ReturnStrById("szRegistrationEmail") . "</p>

					</td>
					<![endif]-->

					<td>

						<input " . ($validationResponse & (Controller::REGISTRATION_EMAIL_INVALID | Controller::REGISTRATION_EMAIL_TAKEN) ? "style=\"border-color:red;\"" : "") . " value=\"" . (array_key_exists('Email', $_POST) ? filter_var($_POST['Email'], FILTER_SANITIZE_STRING) : "") . "\" name=\"Email\" type=\"text\" maxlength=\"100\" size=\"35\" placeholder=\"" . Locale::ReturnStrById("szRegistrationEmail") . "\" />

						<font color=\"orangered\" size=\"+1\"><tt><b>*</b></tt></font>

					</td>

				</tr>

				<tr>

					<!--[if lte IE 9]>
					<td align=\"right\">

						<p>" . Locale::ReturnStrById("szRegistrationRepeatEmail") . "</p>

					</td>
					<![endif]-->

					<td>

						<input " . ($validationResponse & Controller::REGISTRATION_EMAIL_NOT_MATCH ? "style=\"border-color:red;\"" : "") . " value=\"" . (array_key_exists('RepeatEmail', $_POST) ? filter_var($_POST['RepeatEmail'], FILTER_SANITIZE_STRING) : "") . "\" name=\"RepeatEmail\" type=\"text\" maxlength=\"100\" size=\"35\" placeholder=\"" . Locale::ReturnStrById("szRegistrationRepeatEmail") . "\" />

						<font color=\"orangered\" size=\"+1\"><tt><b>*</b></tt></font>

					</td>

				</tr>

				<tr>

					<!--[if lte IE 9]>
					<td align=\"right\">

						<p>" . Locale::ReturnStrById("szRegistrationPassword") . "</p>

					</td>
					<![endif]-->

					<td>

						<input " . ($validationResponse & Controller::REGISTRATION_PASSWORD_INVALID ? "style=\"border-color:red;\"" : "") . " name=\"Password\" type=\"password\" maxlength=\"32\" size=\"35\" placeholder=\"" . Locale::ReturnStrById("szRegistrationPassword") . "\" />

						<font color=\"orangered\" size=\"+1\"><tt><b>*</b></tt></font>

					</td>

				</tr>

				<tr>

					<!--[if lte IE 9]>
					<td align=\"right\">

						<p>" . Locale::ReturnStrById("szRegistrationRepeatPassword") . "</p>

					</td>
					<![endif]-->

					<td>

						<input " . ($validationResponse & Controller::REGISTRATION_PASSWORD_NOT_MATCH ? "style=\"border-color:red;\"" : "") . " name=\"RepeatPassword\" type=\"password\" maxlength=\"32\" size=\"35\" placeholder=\"" . Locale::ReturnStrById("szRegistrationRepeatPassword") . "\" />

						<font color=\"orangered\" size=\"+1\"><tt><b>*</b></tt></font>

					</td>

				</tr>

				<tr>

					<td align=\"right\" colspan=\"2\">

						<hr noshade=\"noshade\" />

						<input type=\"reset\" value=\"" . Locale::ReturnStrById("szRegistrationReset") . "\" />

						<input type=\"submit\" name=\"Submit\" value=\"" . Locale::ReturnStrById("szRegistrationSubmit") . "\" />

					</td>

				</tr>

			</table>

			</form>
			</br></br>
		";

		return $ret;
	}
} 