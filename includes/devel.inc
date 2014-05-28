<?php

/**
 * @file devel.inc
 *  If Devel is enabled, turn on our debug functions
 */

/**
 * Debug var_dump
 *  If you install Xdebug, it will make a prettier output.
 * @param type $foo
 */
function _debug($foo) {
  ini_set('display_errors', 'On');
  error_reporting(E_ALL | E_STRICT);
  $entity = array();
  debug($entity, 'Some label', true); 
  exit();
}

/**
 * Krumo, with a breakpoint.
 * @param type $foo
 */
function kbr($foo = NULL) {
  kpr($foo);
  exit();
}
