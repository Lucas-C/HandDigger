.. -*- coding: utf-8 -*-

.. _contact: lucas.cimon__AT__ensimag.fr

Repo GIT pour le projet Ensimag post-WIMP "contrôle intuituif de pelle mécanique".

.. sectnum::


================
Liste des tâches
================

Par ordre d'importance décroissant :

- Débuter rapport

- Finir algo de répérage des marqueurs

- Inclure modèle 3D avec Windows SDK

- Mettre en place le calibrage

- Ajouter au modèle 3D le godet

- Gérer l'élongation max du modèle 3D


BONUS:

- vues dans multiples fenêtres



===========
Description
===========

Protocole
=========

Marqueurs-balles de ping-pong


? résolution des images ?

? fréquence ?


Calibrage avec feuille contenant marqueurs positionnée à différentes distances

=> fonction de correspondance à associer à interpolation

=> automatisable en une prise



Traitement d'image
==================

Recherche intelligente :

- tenir compte de dernière position

- parcours du tableau avec pas = taille min image



======
Outils
======

GLUT
====


Lib Freenect
============

NOTE: commande d'execution "sudo LD_LIBRARY_PATH=`pwd`/freenect_cpp/lib/ ./cppview"


Lib Kinnect OpenNI/NITE
=======================
http://www.xboxgen.fr/installer-kinect-pc-article-4815-1.html
-> Agidyne | Skyrim99

Key NITE: 0KOIk2JeIBYClPWVnMoRKn5cdY4=

http://tirokartblog.wordpress.com/2011/01/21/kinect-working-on-ubuntu-10-10/


Window Kinnect SDK
==================
