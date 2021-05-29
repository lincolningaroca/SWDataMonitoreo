--
-- PostgreSQL database dump
--

-- Dumped from database version 12.3
-- Dumped by pg_dump version 13.3

-- Started on 2021-05-28 22:57:33

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 210 (class 1255 OID 16555)
-- Name: datos_monit(character, date, time without time zone, text, bytea, bytea, bytea, integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.datos_monit(cod_estacion character, fecha date, hora time without time zone, des text, f1 bytea, f2 bytea, f3 bytea, id_cli integer) RETURNS text
    LANGUAGE plpgsql
    AS $$
									   DECLARE
									   codigo text;
									   BEGIN
									   INSERT INTO datos_monitoreo(codigo_estacion, fecha_muestra,hora_muestra,
                   						descripcion, foto_1, foto_2, foto3, id_cliente)
                  						VALUES(cod_estacion,fecha,hora,des,f1,f2,f3,id_cli)
										RETURNING codigo_estacion INTO codigo;
										
										RETURN codigo;
										END;
										$$;


ALTER FUNCTION public.datos_monit(cod_estacion character, fecha date, hora time without time zone, des text, f1 bytea, f2 bytea, f3 bytea, id_cli integer) OWNER TO postgres;

--
-- TOC entry 211 (class 1255 OID 16654)
-- Name: listar(character); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.listar(mes character) RETURNS TABLE(id integer, cod character)
    LANGUAGE sql
    AS $$
SELECT id_estacion,codigo_estacion FROM datos_monitoreo 
WHERE fecha_muestra::text SIMILAR TO '%-'||mes||'-%';
$$;


ALTER FUNCTION public.listar(mes character) OWNER TO postgres;

--
-- TOC entry 212 (class 1255 OID 16659)
-- Name: listar_por_fecha(integer, integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.listar_por_fecha(integer, integer) RETURNS TABLE(id integer, cod character)
    LANGUAGE sql
    AS $_$
select id_estacion,codigo_estacion from datos_monitoreo where extract(year from fecha_muestra)=$1 and
extract(month from fecha_muestra)=$2
$_$;


ALTER FUNCTION public.listar_por_fecha(integer, integer) OWNER TO postgres;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 205 (class 1259 OID 16494)
-- Name: cliente; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.cliente (
    id integer NOT NULL,
    nombre_unidad character varying(255) NOT NULL,
    descripcion text,
    id_grupo integer NOT NULL
);


ALTER TABLE public.cliente OWNER TO postgres;

--
-- TOC entry 204 (class 1259 OID 16492)
-- Name: cliente_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.cliente_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.cliente_id_seq OWNER TO postgres;

--
-- TOC entry 2862 (class 0 OID 0)
-- Dependencies: 204
-- Name: cliente_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.cliente_id_seq OWNED BY public.cliente.id;


--
-- TOC entry 207 (class 1259 OID 16574)
-- Name: datos_monitoreo; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.datos_monitoreo (
    id_estacion integer NOT NULL,
    codigo_estacion character(50) NOT NULL,
    fecha_muestra date NOT NULL,
    hora_muestra time without time zone NOT NULL,
    descripcion text,
    foto_1 bytea NOT NULL,
    foto_2 bytea,
    foto3 bytea,
    id_cliente integer NOT NULL
);


ALTER TABLE public.datos_monitoreo OWNER TO postgres;

--
-- TOC entry 206 (class 1259 OID 16572)
-- Name: datos_monitoreo_id_estacion_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.datos_monitoreo_id_estacion_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.datos_monitoreo_id_estacion_seq OWNER TO postgres;

--
-- TOC entry 2863 (class 0 OID 0)
-- Dependencies: 206
-- Name: datos_monitoreo_id_estacion_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.datos_monitoreo_id_estacion_seq OWNED BY public.datos_monitoreo.id_estacion;


--
-- TOC entry 203 (class 1259 OID 16483)
-- Name: grupo_minero; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.grupo_minero (
    id integer NOT NULL,
    nombre_grupo character varying(255) NOT NULL,
    descripcion text
);


ALTER TABLE public.grupo_minero OWNER TO postgres;

--
-- TOC entry 202 (class 1259 OID 16481)
-- Name: grupo_minero_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.grupo_minero_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.grupo_minero_id_seq OWNER TO postgres;

--
-- TOC entry 2864 (class 0 OID 0)
-- Dependencies: 202
-- Name: grupo_minero_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.grupo_minero_id_seq OWNED BY public.grupo_minero.id;


--
-- TOC entry 209 (class 1259 OID 16594)
-- Name: parametro_campo; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.parametro_campo (
    nro integer NOT NULL,
    ph numeric,
    tem numeric,
    od numeric,
    ce numeric,
    id_est integer NOT NULL
);


ALTER TABLE public.parametro_campo OWNER TO postgres;

--
-- TOC entry 208 (class 1259 OID 16592)
-- Name: parametro_campo_nro_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.parametro_campo_nro_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.parametro_campo_nro_seq OWNER TO postgres;

--
-- TOC entry 2865 (class 0 OID 0)
-- Dependencies: 208
-- Name: parametro_campo_nro_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.parametro_campo_nro_seq OWNED BY public.parametro_campo.nro;


--
-- TOC entry 2713 (class 2604 OID 16497)
-- Name: cliente id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.cliente ALTER COLUMN id SET DEFAULT nextval('public.cliente_id_seq'::regclass);


--
-- TOC entry 2714 (class 2604 OID 16577)
-- Name: datos_monitoreo id_estacion; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.datos_monitoreo ALTER COLUMN id_estacion SET DEFAULT nextval('public.datos_monitoreo_id_estacion_seq'::regclass);


--
-- TOC entry 2712 (class 2604 OID 16486)
-- Name: grupo_minero id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.grupo_minero ALTER COLUMN id SET DEFAULT nextval('public.grupo_minero_id_seq'::regclass);


--
-- TOC entry 2715 (class 2604 OID 16597)
-- Name: parametro_campo nro; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.parametro_campo ALTER COLUMN nro SET DEFAULT nextval('public.parametro_campo_nro_seq'::regclass);


--
-- TOC entry 2721 (class 2606 OID 16502)
-- Name: cliente cliente_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.cliente
    ADD CONSTRAINT cliente_pkey PRIMARY KEY (id);


--
-- TOC entry 2725 (class 2606 OID 16582)
-- Name: datos_monitoreo datos_monitoreo_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.datos_monitoreo
    ADD CONSTRAINT datos_monitoreo_pkey PRIMARY KEY (id_estacion);


--
-- TOC entry 2717 (class 2606 OID 16491)
-- Name: grupo_minero grupo_minero_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.grupo_minero
    ADD CONSTRAINT grupo_minero_pkey PRIMARY KEY (id);


--
-- TOC entry 2727 (class 2606 OID 16602)
-- Name: parametro_campo parametro_campo_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.parametro_campo
    ADD CONSTRAINT parametro_campo_pkey PRIMARY KEY (nro, id_est);


--
-- TOC entry 2719 (class 2606 OID 16538)
-- Name: grupo_minero unique_name; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.grupo_minero
    ADD CONSTRAINT unique_name UNIQUE (nombre_grupo);


--
-- TOC entry 2723 (class 2606 OID 16540)
-- Name: cliente unique_nombre_unidad; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.cliente
    ADD CONSTRAINT unique_nombre_unidad UNIQUE (nombre_unidad);


--
-- TOC entry 2729 (class 2606 OID 16583)
-- Name: datos_monitoreo datos_monitoreo_id_cliente_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.datos_monitoreo
    ADD CONSTRAINT datos_monitoreo_id_cliente_fkey FOREIGN KEY (id_cliente) REFERENCES public.cliente(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 2728 (class 2606 OID 16503)
-- Name: cliente grupo_cliente; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.cliente
    ADD CONSTRAINT grupo_cliente FOREIGN KEY (id_grupo) REFERENCES public.grupo_minero(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 2730 (class 2606 OID 16603)
-- Name: parametro_campo parametro_campo_id_est_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.parametro_campo
    ADD CONSTRAINT parametro_campo_id_est_fkey FOREIGN KEY (id_est) REFERENCES public.datos_monitoreo(id_estacion) ON UPDATE CASCADE ON DELETE CASCADE;


-- Completed on 2021-05-28 22:57:34

--
-- PostgreSQL database dump complete
--

