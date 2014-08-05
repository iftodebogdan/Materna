<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 26/07/14
 * Time: 19:49
 */

namespace Utils\Performance;

//error_reporting(0);
$repetitions = 10000;

class PerformanceHelper
{
	private static function getmicrotime()
	{
		$t = gettimeofday();
		return $t['sec'] * 1000 + $t['usec'] / 1000;
	}

	private static function bench()
	{
		static $start;
		if (! $start)
		{
			$start = self::getmicrotime();
			return;
		}
		$duration = self::getmicrotime() - $start;
		$start = 0;
		return $duration;
	}

	private static function ms($ms)
	{
		echo '<td>';
		if ($ms <= 0)
			echo 0;
		else if ($ms < 0.5)
			echo '&gt;0';
		else
			echo (int) round($ms);
		echo '&nbsp;ms</td>';
	}

	private static function display_bench_results()
	{
		$html = ob_get_clean();
		preg_match_all('/>\{([^}]+)\}/is', $html, $matches);
		$min = 0;
		$sum = 0;
		foreach ($matches[1] as $i => $s)
		{
			if ($min <= 0)
				$min = floatval($s);
			else
				$min = min($min, floatval($s));
			$sum += floatval($s);
		}
		foreach ($matches[1] as $i => $s)
		{
			$index = (int) round(floatval($s) * 100 / $min);
			if ($index > 5000) $class = 'no';
			elseif ($index > 500) $class = 'buggy';
			elseif ($index > 200) $class = 'incomplete';
			elseif ($index > 100) $class = 'almost';
			else $class = 'yes';
			$html = str_replace($matches[0][$i],
			                    ' class="' . $class . '">' . $index, $html);
		}
		echo $html;
		//echo "Total: " . round($sum) . " ms";
	}

	//------------------------------------------------------------------------------

	private static function strcmp_bench($method)
	{
		$r = (int) round($GLOBALS['repetitions']);

		self::bench();
		$caption = self::$method("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", $r);
		$d = self::bench();
		$sum = $d;
		echo '<tr><td><code>' . $caption . '</code></td>';
		self::ms($d);

		self::bench();
		self::$method("0bcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", $r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::bench();
		self::$method("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxy0", $r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::ms($sum);
		echo '<td>{' . $sum . '}</td></tr>';
	}

	private static function strcmp_method1($var, $r)
	{
		$equal = false;
		$b = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
		while ($r--)
		{
			$equal = $var == $b;
		}
		return '$a == $b';
	}

	private static function strcmp_method2($var, $r)
	{
		$equal = false;
		$b = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
		while ($r--)
		{
			$equal = !strcmp($var, $b);
		}
		return '!strcmp($a, $b)';
	}

	private static function strcmp_method3($var, $r)
	{
		$equal = false;
		$b = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
		while ($r--)
		{
			$equal = strcmp($var, $b) == 0;
		}
		return 'strcmp($a, $b) == 0';
	}

	private static function strcmp_method4($var, $r)
	{
		$equal = false;
		$b = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
		while ($r--)
		{
			$equal = strcmp($var, $b) === 0;
		}
		return 'strcmp($a, $b) === 0';
	}

	private static function strcmp_method5($var, $r)
	{
		$equal = false;
		$b = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
		while ($r--)
		{
			$equal = strcasecmp($var, $b) === 0;
		}
		return 'strcasecmp($a, $b) === 0';
	}

//------------------------------------------------------------------------------

	private static function array_get_bench($method)
	{
		$array = array();
		for ($i = 0; $i < 100; $i++)
		{
			$array[$i] = "i" . $i;
			$array["key" . $i] = "s" . $i;
		}
		$r = (int) round($GLOBALS['repetitions'] / 4);

		self::bench();
		$caption = self::$method($array, $r);
		$d = self::bench();
		echo '<tr><td><code>' . $caption . '</code></td>';
		self::ms($d);
		echo '<td>{' . $d . '}</td></tr>';
	}

	private static function array_get_method1($array, $r)
	{
		while ($r--)
		{
			for ($i = 0; $i < 100; $i++) $result = $array[$i];
		}
		return '$array[0]';
	}

	private static function array_get_method2($array, $r)
	{
		while ($r--)
		{
			for ($i = 0; $i < 100; $i++) $result = $array[$i];
		}
		return '$array[\'key\']';
	}

//------------------------------------------------------------------------------

	private static function empty_bench($method)
	{
		$r = (int) round($GLOBALS['repetitions'] / 3);

		self::bench();
		$caption = self::$method(
			-1,
			$r);
		$d = self::bench();
		$sum = $d;
		echo '<tr><td><code>' . $caption . '</code></td>';
		self::ms($d);

		self::bench();
		self::$method(
			null,
			$r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::bench();
		self::$method(
			false,
			$r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::bench();
		self::$method(
			"",
			$r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::bench();
		self::$method(
			"0",
			$r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::bench();
		self::$method(
			"1",
			$r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::bench();
		self::$method(
			"12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890",
			$r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::ms($sum);
		echo '<td>{' . $sum . '}</td></tr>';
	}

	private static function empty_method1($var, $r)
	{
		if ($var < 0) unset($var);
		$isEmpty = false;
		while ($r--)
		{
			if (!$var) { $isEmpty = true; }
		}
		//if (empty($var) != $isEmpty) var_dump($var, 'if (!$var)');
		return 'if (!$var)';
	}

	private static function empty_method2($var, $r)
	{
		if ($var < 0) unset($var);
		$isEmpty = false;
		while ($r--)
		{
			if (empty($var)) { $isEmpty = true; }
		}
		//if (empty($var) != $isEmpty) var_dump($var, 'if (empty($var))');
		return 'if (empty($var))';
	}

	private static function empty_method3($var, $r)
	{
		if ($var < 0) unset($var);
		$isEmpty = false;
		while ($r--)
		{
			if ($var == "") { $isEmpty = true; }
		}
		//if (empty($var) != $isEmpty) var_dump($var, 'if ($var == "")');
		return 'if ($var == "")';
	}

	private static function empty_method4($var, $r)
	{
		if ($var < 0) unset($var);
		$isEmpty = false;
		while ($r--)
		{
			if ("" == $var) { $isEmpty = true; }
		}
		//if (empty($var) != $isEmpty) var_dump($var, 'if ("" == $var)');
		return 'if ("" == $var)';
	}

	private static function empty_method5($var, $r)
	{
		if ($var < 0) unset($var);
		$isEmpty = false;
		while ($r--)
		{
			if ($var === "") { $isEmpty = true; }
		}
		//if (empty($var) != $isEmpty) var_dump($var, 'if ($var === "")');
		return 'if ($var === "")';
	}

	private static function empty_method6($var, $r)
	{
		if ($var < 0) unset($var);
		$isEmpty = false;
		while ($r--)
		{
			if ("" === $var) { $isEmpty = true; }
		}
		//if (empty($var) != $isEmpty) var_dump($var, 'if ("" === $var)');
		return 'if ("" === $var)';
	}

	private static function empty_method7($var, $r)
	{
		if ($var < 0) unset($var);
		$isEmpty = false;
		while ($r--)
		{
			if (strcmp($var, "") == 0) { $isEmpty = true; }
		}
		//if (empty($var) != $isEmpty) var_dump($var, 'if (strcmp($var, "") == 0)');
		return 'if (strcmp($var, "") == 0)';
	}

	private static function empty_method8($var, $r)
	{
		if ($var < 0) unset($var);
		$isEmpty = false;
		while ($r--)
		{
			if (strcmp("", $var) == 0) { $isEmpty = true; }
		}
		//if (empty($var) != $isEmpty) var_dump($var, 'if (strcmp("", $var) == 0)');
		return 'if (strcmp("", $var) == 0)';
	}

	private static function empty_method9($var, $r)
	{
		if ($var < 0) unset($var);
		$isEmpty = false;
		while ($r--)
		{
			if (strlen($var) == 0) { $isEmpty = true; }
		}
		//if (empty($var) != $isEmpty) var_dump($var, 'if (strlen($var) == 0)');
		return 'if (strlen($var) == 0)';
	}

	private static function empty_method10($var, $r)
	{
		if ($var < 0) unset($var);
		$isEmpty = false;
		while ($r--)
		{
			if (!strlen($var)) { $isEmpty = true; }
		}
		//if (empty($var) != $isEmpty) var_dump($var, 'if (!strlen($var))');
		return 'if (!strlen($var))';
	}

	//------------------------------------------------------------------------------

	private static function strstr_bench($method)
	{
		$r = (int) round($GLOBALS['repetitions'] / 4);

		self::bench();
		$caption = self::$method(
			"12345678901234567890123456789012345678901234567890123456789012341234567890123456789012345678901234567890123456789012345678901234",
			"abcd", $r);
		$d = self::bench();
		$sum = $d;
		echo '<tr><td><code>' . $caption . '</code></td>';
		self::ms($d);

		self::bench();
		self::$method(
			"abcd5678901234567890123456789012345678901234567890123456789012341234567890123456789012345678901234567890123456789012345678901234",
			"abcd", $r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::bench();
		self::$method(
			"12345678901234567890123456789012345678901234567890123456789012abcd34567890123456789012345678901234567890123456789012345678901234",
			"abcd", $r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::bench();
		self::$method(
			"1234567890123456789012345678901234567890123456789012345678901234123456789012345678901234567890123456789012345678901234567890abcd",
			"abcd", $r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::ms($sum);
		echo '<td>{' . $sum . '}</td></tr>';
	}

	private static function strstr_method1($haystack, $needle, $r)
	{
		$found = false;
		while ($r--)
		{
			if (strstr($haystack, $needle)) { $found = true; }
		}
		return 'strstr($haystack, $needle)';
	}

	private static function strstr_method2($haystack, $needle, $r)
	{
		$found = false;
		while ($r--)
		{
			if (strpos($haystack, $needle) !== false) { $found = true; }
		}
		return 'strpos($haystack, $needle) !== false';
	}

	private static function strstr_method3($haystack, $needle, $r)
	{
		$found = false;
		while ($r--)
		{
			if (strstr($haystack, $needle) !== false) { $found = true; }
		}
		return 'strstr($haystack, $needle) !== false';
	}

	private static function strstr_method4($haystack, $needle, $r)
	{
		$found = false;
		while ($r--)
		{
			if (stristr($haystack, $needle)) { $found = true; }
		}
		return 'stristr($haystack, $needle)';
	}

	private static function strstr_method5($haystack, $needle, $r)
	{
		$found = false;
		$regexp = '/' . preg_quote($needle, '/') . '/';
		while ($r--)
		{
			if (preg_match($regexp, $haystack)) { $found = true; }
		}
		return 'preg_match("/$needle/", $haystack)';
	}

	private static function strstr_method6($haystack, $needle, $r)
	{
		$found = false;
		$regexp = '/' . preg_quote($needle, '/') . '/i';
		while ($r--)
		{
			if (preg_match($regexp, $haystack)) { $found = true; }
		}
		return 'preg_match("/$needle/i", $haystack)';
	}

	private static function strstr_method7($haystack, $needle, $r)
	{
		$found = false;
		$regexp = '/' . preg_quote($needle, '/') . '/S';
		while ($r--)
		{
			if (preg_match($regexp, $haystack)) { $found = true; }
		}
		return 'preg_match("/$needle/S", $haystack)';
	}

	private static function strstr_method8($haystack, $needle, $r)
	{
		$found = false;
		while ($r--)
		{
			if (ereg($needle, $haystack)) { $found = true; }
		}
		return 'ereg($needle, $haystack)';
	}

//------------------------------------------------------------------------------

	private static function startsWith_method1($haystack, $needle, $r)
	{
		while ($r--)
		{
			$result = strncmp($haystack, $needle, strlen($needle)) === 0;
		}
		return 'strncmp($haystack, $needle, strlen($needle)) === 0';
	}

	private static function startsWith_method2($haystack, $needle, $r)
	{
		while ($r--)
		{
			$result = strncmp($haystack, "abcd", 4) === 0;
		}
		return 'strncmp($haystack, "Test", 4) === 0';
	}

	private static function startsWith_method3($haystack, $needle, $r)
	{
		while ($r--)
		{
			$result = strncasecmp($haystack, $needle, strlen($needle)) === 0;
		}
		return 'strncasecmp($haystack, $needle, strlen($needle)) === 0';
	}

	private static function startsWith_method4($haystack, $needle, $r)
	{
		while ($r--)
		{
			$result = strpos($haystack, $needle) === 0;
		}
		return 'strpos($haystack, $needle) === 0';
	}

	private static function startsWith_method5($haystack, $needle, $r)
	{
		while ($r--)
		{
			$result = substr($haystack, 0, strlen($needle)) === $needle;
		}
		return 'substr($haystack, 0, strlen($needle)) === $needle';
	}

	private static function startsWith_method6($haystack, $needle, $r)
	{
		while ($r--)
		{
			$result = strcmp(substr($haystack, 0, strlen($needle)), $needle) === 0;
		}
		return 'strcmp(substr($haystack, 0, strlen($needle)), $needle) === 0';
	}

	private static function startsWith_method7($haystack, $needle, $r)
	{
		while ($r--)
		{
			$result = preg_match("/^" . preg_quote($needle, "/") . "/", $haystack);
		}
		return 'preg_match("/^" . preg_quote($needle, "/") . "/", $haystack)';
	}

	//------------------------------------------------------------------------------

	private static function endsWith_method1($haystack, $needle, $r)
	{
		while ($r--)
		{
			$result = substr($haystack, strlen($haystack) - strlen($needle)) === $needle;
		}
		return 'substr($haystack, strlen($haystack) - strlen($needle)) === $needle';
	}

	private static function endsWith_method2($haystack, $needle, $r)
	{
		while ($r--)
		{
			$result = substr($haystack, -strlen($needle)) === $needle;
		}
		return 'substr($haystack, -strlen($needle)) === $needle';
	}

	private static function endsWith_method3($haystack, $needle, $r)
	{
		while ($r--)
		{
			$result = strcmp(substr($haystack, -strlen($needle)), $needle) === 0;
		}
		return 'strcmp(substr($haystack, -strlen($needle)), $needle) === 0';
	}

	private static function endsWith_method4($haystack, $needle, $r)
	{
		while ($r--)
		{
			$result = preg_match("/" . preg_quote($needle, "/") . "$/", $haystack);
		}
		return 'preg_match("/" . preg_quote($needle, "/") . "$/", $haystack)';
	}

	//------------------------------------------------------------------------------

	private static function strreplace_method1($subject, $search, $r)
	{
		$replace = $search;
		while ($r--)
		{
			$result = str_replace($search, $replace, $subject);
		}
		return 'str_replace($search, $replace, $subject)';
	}

	private static function strreplace_method2($subject, $search, $r)
	{
		$replace = $search;
		$regexp = '/' . preg_quote($search, '/') . '/';
		while ($r--)
		{
			$result = preg_replace($regexp, $replace, $subject);
		}
		return 'preg_replace("/$search/", $replace, $subject)';
	}

	private static function strreplace_method3($subject, $search, $r)
	{
		$replace = $search;
		$regexp = '/' . preg_quote($search, '/') . '/S';
		while ($r--)
		{
			$result = preg_replace($regexp, $replace, $subject);
		}
		return 'preg_replace("/$search/S", $replace, $subject)';
	}

	private static function strreplace_method4($subject, $search, $r)
	{
		$replace = $search;
		while ($r--)
		{
			$result = ereg_replace($search, $replace, $subject);
		}
		return 'ereg_replace($search, $replace, $subject)';
	}

	//------------------------------------------------------------------------------

	private static function trim_bench($method)
	{
		$r = (int) round($GLOBALS['repetitions'] / 30);

		self::bench();
		$caption = self::$method(
			"1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890",
			$r);
		$d = self::bench();
		$sum = $d;
		echo '<tr><td><code>' . $caption . '</code></td>';
		self::ms($d);

		self::bench();
		self::$method(
			",,,,,,,,,,,,,,,,,,,,1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890",
			$r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::bench();
		self::$method(
			"1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890,,,,,,,,,,,,,,,,,,,,",
			$r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::bench();
		self::$method(
			",,,,,,,,,,,,,,,,,,,,1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890\n1234567890,,,,,,,,,,,,,,,,,,,,",
			$r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::ms($sum);
		echo '<td>{' . $sum . '}</td></tr>';
	}

	private static function trim_method1($string, $r)
	{
		while ($r--)
		{
			$string = trim($string, ",");
		}
		return 'trim($string, ",")';
	}

	private static function trim_method2($string, $r)
	{
		while ($r--)
		{
			$string = preg_replace('/^,*|,*$/', "", $string);
		}
		return 'preg_replace(\'/^,*|,*$/\', "", $string)';
	}

	private static function trim_method3($string, $r)
	{
		while ($r--)
		{
			$string = preg_replace('/^,*|,*$/m', "", $string);
		}
		return 'preg_replace(\'/^,*|,*$/m\', "", $string)';
	}

	private static function trim_method4($string, $r)
	{
		while ($r--)
		{
			$string = preg_replace('/^,+|,+$/', "", $string);
		}
		return 'preg_replace(\'/^,+|,+$/\', "", $string)';
	}

	private static function trim_method5($string, $r)
	{
		while ($r--)
		{
			$string = preg_replace('/^,+|,+$/m', "", $string);
		}
		return 'preg_replace(\'/^,+|,+$/m\', "", $string)';
	}

	private static function trim_method6($string, $r)
	{
		while ($r--)
		{
			$string = preg_replace('/^,+/', "", preg_replace('/,+$/', "", $string));
		}
		return 'preg_replace(\'/^,+/\', "", preg_replace(\'/,+$/\', "", &hellip;))';
	}

	//------------------------------------------------------------------------------

	private static function split_bench($method)
	{
		$r = (int) round($GLOBALS['repetitions'] / 5);

		self::bench();
		$caption = self::$method(
			"",
			$r);
		$d = self::bench();
		$sum = $d;
		echo '<tr><td><code>' . $caption . '</code></td>';
		self::ms($d);

		self::bench();
		self::$method(
			"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890",
			$r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::bench();
		self::$method(
			"12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890,12345678901234567890",
			$r);
		$d = self::bench();
		$sum += $d;
		self::ms($d);

		self::ms($sum);
		echo '<td>{' . $sum . '}</td></tr>';
	}

	private static function split_method1($string, $r)
	{
		while ($r--)
		{
			$array = explode(",", $string);
		}
		return 'explode(",", $string)';
	}

	private static function split_method2($string, $r)
	{
		while ($r--)
		{
			$array = split(",", $string);
		}
		return 'split(",", $string)';
	}

	private static function split_method3($string, $r)
	{
		while ($r--)
		{
			$array = preg_split("/,/", $string);
		}
		return 'preg_split("/,/", $string)';
	}

	private static function split_method4($string, $r)
	{
		while ($r--)
		{
			preg_match_all('/[^,]+/', $string, $matches);
			$array = $matches[0];
		}
		return 'preg_match_all(\'/[^,]+/\', $string, $matches)';
	}

	//------------------------------------------------------------------------------

	private static function loop_bench($method)
	{
		$array = array();
		$i = 128;
		while ($i--)
		{
			$array[] = "abcd";
		}
		reset($array);

		$r = (int) round($GLOBALS['repetitions'] / 200);

		self::bench();
		$caption = self::$method($array, $r);
		$sum = self::bench();
		echo '<tr><td><code>' . $caption . '</code></td>';
		self::ms($sum);
		echo '<td>{' . $sum . '}</td></tr>';
	}

	private static function loop_method1(&$array, $r)
	{
		$found = false;
		while ($r--)
		{
			for ($i = 0; $i < count($array); $i++)
			{
				$found = true;
			}
		}
		return 'for ($i = 0; $i < count($array); $i++)';
	}

	private static function loop_method2(&$array, $r)
	{
		$found = false;
		while ($r--)
		{
			for ($i = 0, $count = count($array); $i < $count; $i++)
			{
				$found = true;
			}
		}
		return 'for ($i = 0, $count = count($array); $i < $count; $i++)';
	}

	private static function loop_method3(&$array, $r)
	{
		$found = false;
		while ($r--)
		{
			for ($i = count($array) - 1; $i >= 0; $i--)
			{
				$found = true;
			}
		}
		return 'for ($i = count($array) - 1; $i >= 0; $i--)';
	}

	private static function loop_method4(&$array, $r)
	{
		$found = false;
		while ($r--)
		{
			for ($i = count($array) - 1; $i >= 0; --$i)
			{
				$found = true;
			}
		}
		return 'for ($i = count($array) - 1; $i >= 0; --$i)';
	}

	private static function loop_method5(&$array, $r)
	{
		$found = false;
		while ($r--)
		{
			$i = count($array); while ($i--)
		{
			$found = true;
		}
		}
		return '$i = count($array); while ($i--)';
	}

	//------------------------------------------------------------------------------

	private static function concat_bench($method)
	{
		$r = (int) round($GLOBALS['repetitions']);
		self::bench();
		$caption = self::$method($r);
		$sum = self::bench();
		echo '<tr><td><code>' . $caption . '</code></td>';
		self::ms($sum);
		echo '<td>{' . $sum . '}</td></tr>';
	}

	private static function concat_method1($r)
	{
		$array = array("mediumLengthExampleString", "mediumLengthExampleString", "mediumLengthExampleString");
		while ($r--)
		{
			$string = implode(" ", $array);
		}
		return 'implode(" ", $array)';
	}

	private static function concat_method2($r)
	{
		$array = array("mediumLengthExampleString", "mediumLengthExampleString", "mediumLengthExampleString");
		while ($r--)
		{
			$string = "$array[0] $array[1] $array[2]";
		}
		return '"$array[0] $array[1] $array[2]"';
	}

	private static function concat_method3($r)
	{
		$array = array("mediumLengthExampleString", "mediumLengthExampleString", "mediumLengthExampleString");
		while ($r--)
		{
			$string = $array[0] . " " . $array[1] . " " . $array[2];
		}
		return '$array[0] . " " . $array[1] . " " . $array[2]';
	}

	private static function concat_method4($r)
	{
		$array = array("mediumLengthExampleString", "mediumLengthExampleString", "mediumLengthExampleString");
		while ($r--)
		{
			$string = sprintf("%s %s %s", $array[0], $array[1], $array[2]);
		}
		return 'sprintf("%s %s %s", $array[0], $array[1], $array[2])';
	}

	private static function concat_method5($r)
	{
		$array = array("mediumLengthExampleString", "mediumLengthExampleString", "mediumLengthExampleString");
		while ($r--)
		{
			$string = vsprintf("%s %s %s", $array);
		}
		return 'vsprintf("%s %s %s", $array)';
	}

	//------------------------------------------------------------------------------

	private static function quotes_bench($method)
	{
		$r = (int) round($GLOBALS['repetitions'] / 2);
		self::bench();
		$caption = self::$method($r);
		$sum = self::bench();
		echo '<tr><td><code>' . $caption . '</code></td>';
		self::ms($sum);
		echo '<td>{' . $sum . '}</td></tr>';
	}

	private static function quotes_method1($r)
	{
		while ($r--)
		{
			$string = '12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678';
		}
		return '\'contains no dollar signs\'';
	}

	private static function quotes_method2($r)
	{
		while ($r--)
		{
			$string = "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678";
		}
		return '"contains no dollar signs"';
	}

	private static function quotes_method3($r)
	{
		while ($r--)
		{
			$string = '1234567890 $a 1234567890 $a 1234567890 $a 1234567890 $a 1234567890 $a 1234567890 $a 1234567890 $a 1234567890 $a 1234567890 $a 12';
		}
		return '\'$variables $are $not $replaced\'';
	}

	private static function quotes_method4($r)
	{
		while ($r--)
		{
			$string = "1234567890 \$a 1234567890 \$a 1234567890 \$a 1234567890 \$a 1234567890 \$a 1234567890 \$a 1234567890 \$a 1234567890 \$a 1234567890 \$a 12";
		}
		return '"\\$variables \\$are \\$not \\$replaced"';
	}

	private static function quotes_method5($r)
	{
		$a = '$a';
		while ($r--)
		{
			$string = "1234567890 $a 1234567890 $a 1234567890 $a 1234567890 $a 1234567890 $a 1234567890 $a 1234567890 $a 1234567890 $a 1234567890 $a 12";
		}
		return '"$variables $are $replaced"';
	}

	private static function quotes_method6($r)
	{
		$a = '$a';
		while ($r--)
		{
			$string = '1234567890 ' . $a . ' 1234567890 ' . $a . ' 1234567890 ' . $a . ' 1234567890 ' . $a . ' 1234567890 ' . $a . ' 1234567890 ' . $a . ' 1234567890 ' . $a . ' 1234567890 ' . $a . ' 1234567890 ' . $a . ' 12';
		}
		return '$variables . \' \' . $are . \' \' . $replaced';
	}

	private static function quotes_method7($r)
	{
		$a = '$a';
		while ($r--)
		{
			$string = "1234567890 " . $a . " 1234567890 " . $a . " 1234567890 " . $a . " 1234567890 " . $a . " 1234567890 " . $a . " 1234567890 " . $a . " 1234567890 " . $a . " 1234567890 " . $a . " 1234567890 " . $a . " 12";
		}
		return '$variables . " " . $are . " " . $replaced';
	}

	public static function RunBenchmark()
	{
		echo '
			<style type="text/css">
				body{
				background:#FFF;
				color:#333;
				font:12px Verdana,sans-serif;
					}
					h1,h2,h3{
				color:#000;
				font-family:"Lucida Sans","Lucida Sans Unicode",Verdana,sans-serif;
						margin:1.5em 0 0.5em;
						padding:0;
						text-shadow:#CCC 2px 2px 4px;
					}
					h1{margin-top:0}
					address{
				font-style:normal;
						margin:1.5em 0;
						text-align:right;
					}
					a{
				border-bottom:1px dashed #BBB;
						color:#000;
						font-weight:bold;
						text-decoration:none;
					}
					a:hover{
				border:0;
				color:#00F;
				text-decoration:underline;
					}
					table{
				border-collapse:separate;
						border-spacing:1px;
						empty-cells:show;
					}
					tr:hover{background:#EEF}
					th,td{
				padding:0.2em 1em;
						text-align:left;
						vertical-align:top;
					}
					th{
				background:#777;
				color:#FFF;
				padding:0.4em 1em;
					}
					td{border-bottom:1px solid #DDD}
					td.right,td+td{text-align:right}
					td a{border:0}
					.yes{
				background:#00882D;
				border:0;
				color:#FFF;
			}
					.almost{
				background:#40A662;
				border:0;
				color:#FFF;
			}
					.incomplete{
				border:1px solid #00882D;
						color:#00882D;
					}
					.buggy{
				background:#DA4C57;
				border:0;
				color:#FFF;
			}
					.no{
				background:#CB000F;
				border:0;
				color:#FFF;
			}
			</style>

			<h1>PHP Performance Benchmarks</h1>

			<p>PHP version ' . phpversion() . ' is running on this server.
			The benchmarks are done live. Reload the page to get fresh numbers.
			</p>

			<h2>Check if a String is empty</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Undefined</th>
					<th>Null</th>
					<th>False</th>
					<th>Empty string</th>
					<th>String "0"</th>
					<th>String "1"</th>
					<th>Long string</th>
					<th>Summary</th>
					<th>Index</th>
				</tr>';

		ob_start();
		for ($i = 1; ; $i++)
		{
			$method = 'empty_method' . $i;
			if (!method_exists(__CLASS__, $method))
				break;
			self::empty_bench($method);
		}
		self::display_bench_results();

		echo '
			</table>
			<p>Conclusion:
				In most cases, use <code>empty()</code> because it does not trigger a warning when used with undefined variables.
				Note that <code>empty("0")</code> returns true.
				Use <code>strlen()</code> if you want to detect <code>"0"</code>.
				Try to avoid <code>==</code> at all because it may cause strange behaviour
				(e.g. <code>"9a" == 9</code> returns true).
				Prefer <code>===</code> over <code>==</code> and <code>!==</code> over <code>!=</code> if possible
				because it does compare the variable types in addition to the contents.
			</p>

			<h2>Compare two Strings</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Equal</th>
					<th>First character not equal</th>
					<th>Last character not equal</th>
					<th>Summary</th>
					<th>Index</th>
				</tr>';

		ob_start();
		for ($i = 1; ; $i++)
		{
			$method = 'strcmp_method' . $i;
			if (!method_exists(__CLASS__, $method))
				break;
			self::strcmp_bench($method);
		}
		self::display_bench_results();

		echo '
			</table>
			<p>Conclusion: Use what fits your needs.</p>

			<h2>Check if a String contains another String</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Not found</th>
					<th>Found at the start</th>
					<th>Found in the middle</th>
					<th>Found at the end</th>
					<th>Summary</th>
					<th>Index</th>
				</tr>';

		ob_start();
		self::strstr_bench('strstr_method1');
		self::strstr_bench('strstr_method2');
		self::strstr_bench('strstr_method3');
		self::strstr_bench('strstr_method4');
		self::strstr_bench('strstr_method5');
		self::strstr_bench('strstr_method6');
		self::strstr_bench('strstr_method7');
		self::strstr_bench('strstr_method8');
		self::display_bench_results();

		echo '
			</table>
			<p>Conclusion:
				It does not matter if you use <code>strstr()</code> or <code>strpos()</code>.
				Use the <code>preg&hellip;()</code> functions only if you need the power of regular expressions.
				Never use the <code>ereg&hellip;()</code> functions.</p>

			<h2>Check if a String starts with another String</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Not found</th>
					<th>Found at the start</th>
					<th>Found in the middle</th>
					<th>Found at the end</th>
					<th>Summary</th>
					<th>Index</th>
				</tr>';

		ob_start();
		self::strstr_bench('startsWith_method1');
		self::strstr_bench('startsWith_method2');
		self::strstr_bench('startsWith_method3');
		self::strstr_bench('startsWith_method4');
		self::strstr_bench('startsWith_method5');
		self::strstr_bench('startsWith_method6');
		self::strstr_bench('startsWith_method7');
		self::display_bench_results();

		echo '
			</table>
			<p>Conclusion:
				<code>strpos()</code> is very fast and can be used in almost all cases.
				<code>strncmp()</code> is good if you are looking for a constant length needle.</p>

			<h2>Check if a String ends with another String</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Not found</th>
					<th>Found at the start</th>
					<th>Found in the middle</th>
					<th>Found at the end</th>
					<th>Summary</th>
					<th>Index</th>
				</tr>';

		ob_start();
		self::strstr_bench('endsWith_method1');
		self::strstr_bench('endsWith_method2');
		self::strstr_bench('endsWith_method3');
		self::strstr_bench('endsWith_method4');
		self::display_bench_results();

		echo '
			</table>
			<p>Conclusion:
				Using <code>substr()</code> with a negative position is a good trick.</p>

			<h2>Replace a String inside another String</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Not found</th>
					<th>Found at the start</th>
					<th>Found in the middle</th>
					<th>Found at the end</th>
					<th>Summary</th>
					<th>Index</th>
				</tr>';

		ob_start();
		self::strstr_bench('strreplace_method1');
		self::strstr_bench('strreplace_method2');
		self::strstr_bench('strreplace_method3');
		self::strstr_bench('strreplace_method4');
		self::display_bench_results();

		echo '
			</table>
			<p>Conclusion:
				Never use the <code>ereg&hellip;()</code> functions.</p>

			<h2>Trim Characters from the Beginning and End of a String</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Not found</th>
					<th>Found at start</th>
					<th>Found at end</th>
					<th>Found at both sides</th>
					<th>Summary</th>
					<th>Index</th>
				</tr>';

		ob_start();
		self::trim_bench('trim_method1');
		self::trim_bench('trim_method2');
		self::trim_bench('trim_method3');
		self::trim_bench('trim_method4');
		self::trim_bench('trim_method5');
		self::trim_bench('trim_method6');
		self::display_bench_results();

		echo '
			</table>
			<p>Conclusion:
				Always benchmark your regular expressions!
				In this case, with <code>.*</code> you also replace nothing with nothing which takes time
				because there is a lot of &ldquo;nothing&rdquo; in every string.</p>

			<h2>Split a String into an Array</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Empty string</th>
					<th>Single occurrence</th>
					<th>Multiple occurrences</th>
					<th>Summary</th>
					<th>Index</th>
				</tr>';

		ob_start();
		self::split_bench('split_method1');
		self::split_bench('split_method2');
		self::split_bench('split_method3');
		self::split_bench('split_method4');
		self::display_bench_results();

		echo '
			</table>
			<p>Conclusion:
				Don\'t use <code>split()</code>. It\'s deprecated in PHP 5.3 and will be removed in PHP 6.</p>

			<h2>Loop a numerical indexed Array of Strings</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Summary</th>
					<th>Index</th>
				</tr>';

		ob_start();
		self::loop_bench('loop_method1');
		self::loop_bench('loop_method2');
		self::loop_bench('loop_method3');
		self::loop_bench('loop_method4');
		self::loop_bench('loop_method5');
		self::display_bench_results();

		echo '
			</table>
			<p>Conclusion:
				<code>count()</code> is horribly slow. Always precalculate it, if possible.</p>

			<h2>Get Elements from an Array</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Summary</th>
					<th>Index</th>
				</tr>';

		ob_start();
		for ($i = 1; ; $i++)
		{
			$method = 'array_get_method' . $i;
			if (!method_exists(__CLASS__, $method))
				break;
			self::array_get_bench($method);
		}
		self::display_bench_results();

		echo '
			</table>
			<p>Conclusion: I like associative arrays.</p>

			<h2>Implode an Array</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Summary</th>
					<th>Index</th>
				</tr>';

		ob_start();
		self::concat_bench('concat_method1');
		self::concat_bench('concat_method2');
		self::concat_bench('concat_method3');
		self::concat_bench('concat_method4');
		self::concat_bench('concat_method5');
		self::display_bench_results();

		echo '
			</table>
			<p>Conclusion: String concatenation is a cheap operation in PHP. Don\'t waste your time benchmarking this.</p>

			<h2>The single vs. double Quotes Myth</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Summary</th>
					<th>Index</th>
				</tr>';

		ob_start();
		self::quotes_bench('quotes_method1');
		self::quotes_bench('quotes_method2');
		self::quotes_bench('quotes_method3');
		self::quotes_bench('quotes_method4');
		self::quotes_bench('quotes_method5');
		self::quotes_bench('quotes_method6');
		self::quotes_bench('quotes_method7');
		self::display_bench_results();

		echo '
			</table>
			<p>Conclusion:
				It does not matter if you use single or double quotes at all.
				The inclusion of variables has a measurable effect, but that\'s independent from the quotes.</p>

			<h2>Performance of password_hash()</h2>
			<table>
				<tr>
					<th>Method</th>
					<th>Summary</th>
				</tr>';

		$timeTarget = 0.2;

		$cost = 9;
		do {
			$cost++;
			$start = microtime(true);
			password_hash("test", PASSWORD_BCRYPT, ["cost" => $cost]);
			$end = microtime(true);
		} while (($end - $start) < $timeTarget);

		echo '
				<tr>
					<td>Determine how high of a cost you can afford</td>
					<td>' . $cost . '</td>
				<tr/>';

		echo '
			</table>
			<p>Conclusion: You want to set the highest cost that you can without slowing down you server too much. 10 is a good baseline, and more is good if your servers are fast enough.</p>
		';
	}
}
