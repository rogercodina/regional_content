CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Configuration

INTRODUCTION
------------

This Drupal 7 module allows you to filter content given user selected world
region. It also selects a default region for users given their IP (depending
on country IP, the user will be redirected to a region or to another one). It
has the following features:

 * This module defines "Website regions" vocabulary, a block that allows users
   to change the region and a regional filter for views and blocks.

 * When user reaches the web for first time, the user is redirected to a region
   given the country of their IP address and "Website regions" terms hierarchy.

 * Admins can change available regions by editing the "Website regions" taxonomy
   terms. They can also configure which countries are in each region.

 * Admins can filter content by regions in views using "Custom: Regional
   filter". Search API views are also supported.

 * Users can switch between regions by using "Regional content switcher" block
   which is automatically created by this module.

 * This module is a much simple alternative to Domain Access module if you
   just need content regionalization.

INSTALLATION
------------

 * Install as you would normally install a contributed Drupal module. See:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information.

CONFIGURATION
-------------

 * Visit admin/config/user-interface/regional_content to configure the behavior
   of global region. Then edit your regions and countries by clicking on
   "Configure regions and countries" link you will find there. This is a
   hierarchical vocabulary where regions are at top level and countries at 
   second. You can reorder items and add or remove them. WARNING: Remember the
   description of countries must be the two letter country code.
  
 * Edit the content types you want to filter by region and add a field named 
   "Region" (must have "field_regional_content" as its machine name). This field
   must be of type "Entity Reference", must have "Unlimited" values and must
   point to "Website regions" vocabulary. If you use Search API module, remember
   to index the new field in your indexes!

 * Edit your content views and add the filter "Custom: Regional filter" to them.
   From now on, your views will get filtered given user's selected region.

 * Edit your blocks and configure the regions where they should appear.
   
 * IMPORTANT: Move "Regional content switcher" block to a region of your frontend
   theme. THIS BLOCK IS REQUIRED FOR THIS MODULE TO WORK WELL!

 * WARNING: Don't remove GLOBAL region.
