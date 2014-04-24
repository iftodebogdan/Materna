<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/21/14
 * Time: 8:27 PM
 */

//Include debug functions
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//Check if there is a PATH_INFO index
if(!array_key_exists('PATH_INFO', $_SERVER))
    DbgHelper::printDbgMsgAndDie('Index PATH_INFO does not exist in $_SERVER!', DbgHelper::ERROR);

//Parse the PATH_INFO
$userArgs = explode('/', $_SERVER['PATH_INFO']);

//Sanitize input
$userArgs = array_filter($userArgs, 'strlen');

//Check if the user arguments are valid
if( count($userArgs) < 1 )
    DbgHelper::printDbgMsgAndDie('$userArgs is empty!', DbgHelper::ERROR);

//Build class names
$modelClass = $userArgs[1] . 'Model';
$viewClass = $userArgs[1] . 'View';
$controllerClass = $userArgs[1] . 'Controller';

//Include class definitions
require_once("Models/$modelClass.inc");
require_once("Views/$viewClass.inc");
require_once("Controllers/$controllerClass.inc");

//Add namespaces to class names
$modelClass = '\Models\\' . $modelClass;
$viewClass = '\Views\\' . $viewClass;
$controllerClass = '\Controllers\\' . $controllerClass;

//Instantiate modules
$model = new $modelClass();
$controller = new $controllerClass($model);
$view = new $viewClass($controller, $model);
