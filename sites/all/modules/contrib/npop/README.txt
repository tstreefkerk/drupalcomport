***********
* README: *
***********

INSTALLATION:
-------------
1. Place the entire npop directory into your Drupal sites/all/modules/
   directory.
2. Enable the Node popup (npop) module by navigating to:
     administer > modules


HOW TO
------
1. Enable module
2. Create link.
2.1. Variant 1: Set data-npop="NODE_NID" (recomended)
2.2. Variant 2: Set href attribute as "ajax/npop/node/[nid]/load/nojs",
     where [nid] nid of node and set link class "use-ajax".
3. Done

Alternative method of creation link programmatically:
You can use function npop_create_link($title, $nid, $options) Where
   $nid is node NID
   $title is Link title
   $options is link options (see l() function in drupal API)


THEMING
-------
1. You can set fields to view in node display settings page
   admin/structure/types/manage/[NODE_TYPE]/display/npop_ajax
2. You can create template node--[node_type]--npop_ajax.tpl.php

Example: for node type "article" create template
node--article--npop_ajax.tpl.php


Author:
-------
ArmRus (https://www.drupal.org/u/armrus)
admin@armrus.net
