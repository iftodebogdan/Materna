<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/21/14
 * Time: 8:27 PM
 */

//Include debug functions
require_once('Utils/Debug/DbgHelper.php');
use \Utils\Debug\DbgHelper as DbgHelper;

//Include localised string
require_once('Resources/Strings/ro-ro.php');

//Parse the PATH_INFO
$userArgs = explode('/', $_SERVER['PATH_INFO']);

//Sanitize input
$userArgs = array_filter($userArgs, 'strlen');
if( count($userArgs) < 1 )
{
    DbgHelper::printDebugMessage('$userArgs is empty!', DbgHelper::ERROR);
    return;
}

//Build class names
$modelClass = $userArgs[1] . 'Model';
$viewClass = $userArgs[1] . 'View';
$controllerClass = $userArgs[1] . 'Controller';

//Include class definitions
require_once("Models/$modelClass.php");
require_once("Views/$viewClass.php");
require_once("Controllers/$controllerClass.php");

//Add namespaces to class names
$modelClass = '\Models\\' . $modelClass;
$viewClass = '\Views\\' . $viewClass;
$controllerClass = '\Controllers\\' . $controllerClass;

//Instantiate modules
$model = new $modelClass();
$controller = new $controllerClass($model);
$view = new $viewClass($controller, $model);

//Render the view
echo LANG; //$view->output();