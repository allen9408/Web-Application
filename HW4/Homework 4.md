# Homework 4

*Name: Weiqing Ni*

*NetID: wn61*

## 1

**(a) DTD File** 

```dtd
<!DOCTYPE productsBook[
    <!ELEMENT productsBook (products*)>
    <!ELEMENT products (name, price, description, store*)>
    <!ELEMENT store	(name, phone, makeup)>
    <!ELEMENT name 			(#PCDATA)>
    <!ELEMENT price 		(#PCDATA)>
    <!ELEMENT description	(#PCDATA)>
    <!ELEMENT sname			(#PCDATA)>
    <!ELEMENT phone			(#PCDATA)>
    <!ELEMENT makeup		(#PCDATA)>
  ]>
```

**(b)**

```xquery
FOR $a IN document("*.xml")	/db/products
	$c IN document("*.xml")	/db/sells
	RETURN <products>
		{$a/row/name,
		 $a/row/price,
		 $a/row/description,
		 FOR $b IN /db/stores[/row/sid = $c/row/sid and /row/pid = $a/row/pid]
		 RETURN $b/row/name,
		 		$b/row/phone,
		 		$b/row/makeup,
		 	 }
	</products>
```

**(c)**

```xquery
FOR $a IN document("*.xml") /db/products
	$c IN document("*.xml") /db/sells
WHERE $a/rows/pid = $c/row/pid and $c/row/makeup > 25%
RETURN <result>
	   {$a/row/name,
	    $a/row/price,}
	   </result>
```

**(d)**

```sql
SELECT p.name p.price
FROM products.p, sells.s
WHERE p.pid = s.sid and s.makeup > '25%'
```

## 2

**(a)**

```xquery
FOR $a IN document("*.xml")/*/title
RETURN <result>
		{$a}
		</result>
```

**(b)**

```xquery
FOR $a IN document("*.xml")/broadway/theater
LET $b := $a[price le 35]/price
WHERE $a/date = "11/9/2008" and count($b) >= 1
RETURN <result>
		{$a/address,}
		</result>
```

**(c)**

```xquery
FOR $a IN document("*.xml")/broadway/concert
LET $b := $a/concert[type='chamber orchestra']/price
WHERE avg($b) >= 50
RETURN <result>
		{$a/title}
		</result>
```

**(d)**

```xquery
<groupByDate>
for $a in document("x.xml")/broadway/
let $b := distinct-values($a/*/date/text())
for $x in $b
return  <date>
	<day>{$x}
	{for $y in $a/*[date=$x]
	 return {$y}
	 {$y/title}
	 {$y/price}
	}
	</day>
	</date>
	</groupByDate>
```

## 3

**(a)**

```xml
<?xml version="1.0" encoding="ISO-8859-1"?>
<?xml-stylesheet type="text/xsl" href="bid.xsl"?>
<!DOCTYPE bib SYSTEM "bid.dtd">
<bid>
  <book>
    <author>
      <first_name>Leslie</first_name>
      <last_name>Lamport</last_name>
    </author>
    <title>Latex: A Document Presentation System</title>
    <year>1986</year>
    <publisher>Addison-Wesley</publisher>
  </book>

  <article>
    <author>
      <first_name>David</first_name>
      <last_name>Marr</last_name>
    </author>
    <title>Visual information processing</title>
    <year>1980</year>
    <volume>290</volume>
    <page>
      <from>199</from>
      <to>218</to>
    </page>
    <journal>Phil. Trans. Roy, Soc. B</journal>
  </article>

  <article>
    <author>
      <first_name>R.K</first_name>
      <last_name>Clifton</last_name>
    </author>
    <title>Breakdown of echo suppression in the precedence effect</title>
    <year>1987</year>
    <volume>82</volume>
    <page>
      <from>1834</from>
      <to>1835</to>
    </page>
    <journal>J. Acoust. Soc. Am.</journal>
  </article>

  <book>
    <author>
      <first_name>David</first_name>
      <last_name>Marr</last_name>
    </author>
    <title>Vision</title>
    <year>1982</year>
    <address>NY</address>
    <publisher>Freeman</publisher>
  </book>

  <article>
    <author>
      <first_name>David</first_name>
      <last_name>Marr</last_name>
    </author>
    <title>Visual information processing</title>
    <year>1980</year>
    <volume>290</volume>
    <page>
      <from>199</from>
      <to>218</to>
    </page>
    <journal>Phil. Trans. Roy, Soc. B</journal>
  </article>

</bid>
```

**(b)**

```xml
insert node element book{
  <author>
    <first_name>first_name1</first_name>
    <last_name>last_name1</last_name>
  </author>
  <title>title1</title>
  <year>year1</year>
  <publisher>publisher1</publisher>
  <address>address1</address>
} into document("bid.xml")/bid

insert node element book{
  <author>
    <first_name>first_name2</first_name>
    <last_name>last_name2</last_name>
  </author>
  <title>title2</title>
  <year>year2</year>
  <publisher>publisher2</publisher>
  <address>address2</address>
} into document("bid.xml")/bid

insert node element article{
  <author>
    <first_name>first_name3</first_name>
    <last_name>last_name3</last_name>
  </author>
  <title>title3</title>
  <year>year3</year>
  <volume>volume3</volume>
  <page>
    <from>page_from1</from>
    <to>page_to1</to>
  </page>
  <journal>journal1</journal>
}into document("bid.xml")/bid

insert node element article{
  <author>
    <first_name>first_name4</first_name>
    <last_name>last_name4</last_name>
  </author>
  <title>title4</title>
  <year>year4</year>
  <volume>volume4</volume>
  <page>
    <from>page_from2</from>
    <to>page_to2</to>
  </page>
  <journal>journal2</journal>
}into document("bid.xml")/bid
```

**(c)**

Add the following code to DTD file:

```dtd
<!ELEMENT phd_thesis(author, year, title, school)>
<!ELEMENT school (#PCDATA)>
```

xml:

```xml
insert element phd_thesis{
  <author>
    <first_name>first_name5</first_name>
    <last_name>last_name5</last_name>
  </author>
  <year>year5</year>
  <title>title5</title>
  <school>school5</school>
}into document("bid.xml")/bid

insert element phd_thesis{
  <author>
    <first_name>first_name6</first_name>
    <last_name>last_name6</last_name>
  </author>
  <year>year6</year>
  <title>title6</title>
  <school>school6</school>
}into document("bid.xml")/bid
```

