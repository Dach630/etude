<?xml version="1.0" ?>
<xsl:stylesheet version="1.0" 
		xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xsd="http://www.w3.org/2001/XMLSchema"
    xmlns:fun="foobar" exclude-result-prefixes="fun xsd"
		xmlns="http://www.w3.org/2000/svg"
		>


  <xsl:output
    method="xml"
    indent="yes"
    media-type="image/svg" />
  <xsl:key name="node" match="data/node" use="@id" />
  <xsl:param name="tree"/>

  <xsl:variable name="leaf" select="0"/>
  <xsl:template match="root">
      <svg xmlns="http://www.w3.org/2000/svg" width="8000" height="500">


        <xsl:call-template name="test">
          <xsl:with-param name="node" select="tree/node"/>
          <xsl:with-param name="depth" select="0"/>
          <xsl:with-param name="decalage" select="1"/>
        </xsl:call-template>
        
    </svg>
  </xsl:template>

  <xsl:template name="test">
    <xsl:param name="node"/>
    <xsl:param name="depth" as="xsd:double"/>
    <xsl:param name="decalage" as="xsd:double"/>
    <xsl:variable name="x1" select="$decalage * 2"/>
    <xsl:variable name="x2" select="($decalage + count(following::node)) * 2"/>
    <xsl:variable name="y1" select="$depth * 2"/>
    <xsl:variable name="y2" select="($depth * 2) + 2"/>
    <xsl:choose>
      <xsl:when test="count($node/*) != 0"> <!-- node-->

        <xsl:for-each select="$node/*">
          <xsl:variable name="prcleaf" select="count(preceding::node//*[not(./*)])"/>

          <xsl:call-template name="test">
            <xsl:with-param name="node" select="."/>
            <xsl:with-param name="depth" select="$depth + 1"/>
            <xsl:with-param name="decalage" select="$decalage + $prcleaf"/>
          </xsl:call-template>
        </xsl:for-each>

        <xsl:variable name="x3" select="($x1 + $x2) div 2"></xsl:variable>
        <!-- <path x1="{$x1}" y2="{$y2}" x2="{$x2}" d="M x1 y2 H x2"/>
        <path x1="{$x3}" y1="{$y1}" y2="{$y2}" d="M x1 y2 V y2"/> -->
        <line x1="{$x1}" y1="{$y2}" x2="{$x2}" y2="{$y2}" style="stroke:rgb(0,0,0);stroke-width:2"/>
        <line x1="{$x3}" y1="{$y1}" x2="{$x3}" y2="{$y2}" style="stroke:rgb(0,0,0);stroke-width:2"/>
      </xsl:when>
      <xsl:otherwise><!-- leaf-->
        <!-- <path x1="{$x1}" y1="{$y1}" y2="{$y2}" d="M x1 y1 V y2"/> -->
        <line x1="{$x1}" y1="{$y1}" x2="{$x1}" y2="{$y2}" style="stroke:rgb(0,0,0);stroke-width:2"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  

</xsl:stylesheet>
